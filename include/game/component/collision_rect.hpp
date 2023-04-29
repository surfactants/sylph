#pragma once

#include <SFML/Graphics/Rect.hpp>

struct Collision_Rect : public sf::FloatRect {

    void setPosition(sf::Vector2f pos)
    {
        left = pos.x;
        top = pos.y;
    }

    void move(sf::Vector2f offset)
    {
        left += offset.x;
        top += offset.y;
    }

    void setSize(sf::Vector2f size)
    {
        width = size.x;
        height = size.y;
    }
};
