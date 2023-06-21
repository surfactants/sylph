#include <engine/resources/texture_manager.hpp>

#include <engine/database/database_textures.hpp>

#include <iostream>

//////////////////////////////////////////////////////////////

//std::map<std::string, sf::Texture> Texture_Manager::textures;

Texture_Manager* Texture_Manager::instance { nullptr };

Texture_Manager::Texture_Manager()
{
    Database_Textures dbt;
    dbt.read(textures);
}

sf::Texture* Texture_Manager::get(std::string key)
{
    if (instance == nullptr) {
        instance = new Texture_Manager();
    }

    if (instance->textures.count(key)) {
        return &instance->textures[key];
    }
    else {
        std::cout << "FAILED TO FIND TEXTURE OF KEY " << key << "!\n";
    }

    return nullptr;
}
