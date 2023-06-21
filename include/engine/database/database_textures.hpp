#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <map>
#include <string>

#include "database.hpp"

class Database_Textures : Database {
public:
    Database_Textures();

    void read(std::map<std::string, sf::Texture>& textures);
};
