#pragma once

#include <SFML/Graphics/Color.hpp>

#include <string>

struct New_Game_Data {
    std::string player_name;
    sf::Color player_color;
    enum Size {
        SMALL = 0,
        MEDIUM,
        LARGE,
        VERY_LARGE
    };
    Size size { SMALL };
};
