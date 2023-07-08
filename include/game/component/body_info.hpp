#pragma once

#include <SFML/Graphics/Color.hpp>

#include <game/core/entity.hpp>

struct Body_Info {
    std::string type;
    std::string subtype;

    float radius { 0.f };
    float orbit { 0.f };

    float temperature;
    float light;

    sf::Color color;

    float chance;

    bool owned { false };
    Entity owner;
};
