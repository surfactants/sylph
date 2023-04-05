#pragma once

#include <vector>

#include <system/input/command.hpp>
#include <system/input/key_string.hpp>

#include "database.hpp"

class Database_Commands : protected Database {
public:
    Database_Commands() = default;

    std::vector<Command> read();

    void write(std::vector<Command> pkg);

protected:
    void deleteMissingKeys(const std::vector<Command>& pkg);

    Key_String key_string;
};
