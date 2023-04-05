#pragma once

#include "database.hpp"

#include <system/input/input_package.hpp>

class Database_Commands : protected Database {
public:
    Database_Commands();

    Input_Package getInputPackage();

    void write(Input_Package& pkg);
};
