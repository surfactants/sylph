#pragma once

#include <SFML/System/Vector2.hpp>

#include <vector>

#include <game/core/entity.hpp>

struct Polygon_Tile {
    std::vector<sf::Vector2f> vertices;
    sf::Color color { sf::Color::Transparent };
};
