#pragma once

#include <SFML/Graphics/Color.hpp>

#include <game/entity/entity.hpp>

struct Empire_Data {
    Entity capital_system;
    Entity homeworld;
    std::vector<Entity> systems; // includes capital
    float population;
    sf::Color color;
};
