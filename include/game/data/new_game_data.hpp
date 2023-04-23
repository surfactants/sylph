#pragma once

#include <SFML/Graphics/Color.hpp>

#include <string>

struct New_Game_Data {
    std::string player_name;
    sf::Color player_color;
    enum Size {
        SMALL = 0,
        MEDIUM = 1,
        LARGE = 2
    };
    Size size { SMALL };
};
