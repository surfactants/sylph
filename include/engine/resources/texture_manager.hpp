#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <map>

/// TEXTURE MANAGER ///
/// \brief singleton object that stores texture objects and provides references to them
///
class Texture_Manager {
public:

/// get ///
/// \brief returns a reference to the texture keyed to the passed string
///
    static sf::Texture* get(std::string key);

private:
    std::map<std::string, sf::Texture> textures; /**< texture storage */

    static Texture_Manager* instance; /**< singleton instance */

/// DEFAULT CONSTRUCTOR ///
/// \brief loads textures from the database
///
    Texture_Manager();
};
