#include <cmath>
#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
// To measure performance, use
// $ make timep
//
// which relies on the bash command
// $ time (./a.out > results.txt)

class Prime_numbers {
  public:
    Prime_numbers(int num_threads): NUM_THREADS{num_threads} { }

    // Returns true if "number" is a prime number
    bool is_prime (int number) {
      if (number < 2) return false;
      for (int i=2; i <= std::sqrt(number); ++i) {
        if ((number % i) == 0) return false;
      }
      return true;
    }

    // find_primes is the algorithm to be run as multiple threads,
    //     adding each prime found to the shared vector "primes".
    // NOTE: You'll likely need to break out the for loop as a separate
    //     method, which will be the code executed by each thread.
    //     The find_prime method will just create and manage the threads.
    void find_primes_thread(int lower, int upper) {
        for (int i=lower; i<=upper; ++i) {
            if (is_prime(i)) {
                m.lock();
                primes.push_back(i);
                m.unlock();
            }
        }
    }    
    void find_primes(int start,int end){
     int NUM_VALUES_PER_THREAD=((end-start)/(NUM_THREADS));
     int threadStart,threadEnd;
     threadStart=start;
     threadEnd=NUM_VALUES_PER_THREAD;
  
     std::thread t[NUM_THREADS];
     for(int i=0;i<NUM_THREADS;i++){
      t[i]=std::thread((&Prime_numbers::find_primes_thread),this,threadStart,threadEnd);
      threadStart=threadEnd;
      threadEnd=threadEnd+NUM_VALUES_PER_THREAD;
}
    for(int i=0;i<NUM_THREADS;i++){
    t[i].join();
}

}

    typedef std::vector<int> Primes;

    // Iterating Prime_numbers will iterate attribute primes
    typedef Primes::iterator iterator;
    typedef Primes::const_iterator const_iterator;
    iterator begin() {return primes.begin();}
    iterator end() {return primes.end();}

  private:
    std::mutex m;
    const int NUM_THREADS;

    // Vector primes will contain all of the primes found
    Primes primes;
};

int main(int argc, char* argv[]) {
    // Determine number of threads requested
    int threads = 4;
    if(argc > 1) threads = atoi(argv[1]);
    Prime_numbers prime_numbers(threads);

    // Determine maximum integer to search
    int max_int = 3500000;
    if(argc > 2) max_int = atoi(argv[2]);

    // Search and identify all primes between 2 and max_int
    prime_numbers.find_primes(2, max_int);

    // Print all primes that were found  
    for (int p : prime_numbers) std::cout << p << '\n';
    std::cout << std::endl;
}

