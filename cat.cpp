#include "cat.h"


Cat::Cat(Cat_breed breed, std::string name, Gender gender, int age)
    : Animal(name, gender, age), _breed{breed} { }
Cat::~Cat() { }

std::string Cat::family() const {return "cat";}
std::string Cat::breed() const {return ::to_string(_breed);}

    const std::map<Cat_breed, std::string> cats_map = {
        {Cat_breed::MIX                , "Mix"               },
        {Cat_breed::SIAMESE            , "Siamese"           }, 
        {Cat_breed::PERSIAN            , "Persian"           }, 
        {Cat_breed::MAINE_COON         , "Maine Coon"        }, 
        {Cat_breed::RAGDOLL            , "Ragdoll"           }, 
        {Cat_breed::BENGAL             , "Bengal"            }, 
        {Cat_breed::ABYSSINIAN         , "Abyssinian"        }, 
        {Cat_breed::BIRMAN             , "Birman"            }, 
        {Cat_breed::ORIENTAL_SHORTHAIR , "Oriental Shorthair"}, 
        {Cat_breed::DEVON_REX          , "Devon Rex"         }, 
        {Cat_breed::AMERICAN_SHORTHAIR , "American Shorthair"}, 
        {Cat_breed::HIMALAYAN          , "Himalayan"         }, 
    };
std::string to_string(const Cat_breed& breed) {
    try {
        return cats_map.at(breed);
    } catch (std::exception& e) {
        return "Unknown";
    }
}
std::ostream& operator<<(std::ostream& ost, const Cat_breed& breed) {
    ost << ::to_string(breed);
    return ost;
}
