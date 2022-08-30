#ifndef __CLIENT_H
#define __CLIENT_H

#include <string>

class Client {
  public:
    Client(std::string name, std::string phone, std::string email);
    friend std::ostream& operator<<(std::ostream& ost, const Client& client);
  private:
    std::string _name;
    std::string _phone;
    std::string _email;
};

#endif

