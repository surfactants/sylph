#pragma once

#include <map>
#include <vector>

#include <engine/resources/font.hpp>

#include "database.hpp"

class Database_Fonts : public Database {
public:
    void read(std::map<Font, sf::Font>& fonts);

private:
    static std::vector<char*> buffers;
};
