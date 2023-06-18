#pragma once

#include <map>
#include <string>

#include "database.hpp"

class Database_Strings : public Database {
public:
    Database_Strings();

    void read(std::map<std::string, std::string>& strings, std::string language);
};
