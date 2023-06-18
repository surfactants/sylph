#pragma once

#include <string>

#include "database.hpp"

class Database_Settings_General : public Database {
public:
    Database_Settings_General();

    std::string activeLanguage();
};
