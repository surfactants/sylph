#pragma once

#include <SFML/Graphics/Color.hpp>

struct Body_Info {
    std::string name;
    std::string description;

    std::string type;
    std::string subtype;

    float radius { 0.f };
    float orbit { 0.f };

    float temperature;
    float light;

    sf::Color color;

    float chance;
};