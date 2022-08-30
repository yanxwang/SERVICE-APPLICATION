#include "client.h"
#include <iostream>

Client::Client(std::string name, std::string phone, std::string email) : _name{name}, _phone{phone}, _email{email} { }

std::ostream& operator<<(std::ostream& ost, const Client& client) {
    ost << client._name  << " ("
        << client._phone << ", "
        << client._email << ')';
    return ost;
}

