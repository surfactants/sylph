#pragma once

#include <SFML/Graphics/Color.hpp>

#include <game/core/entity.hpp>

struct Civilization_Data {
    Entity capital_system;
    Entity homeworld;
    std::vector<Entity> systems; // includes capital
    float population { 0.f };
    sf::Color color;
};
