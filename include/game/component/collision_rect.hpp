#pragma once

#include <SFML/Graphics/Rect.hpp>

struct Collision_Rect : public sf::FloatRect {
    sf::Vector2f min {0.f, 0.f };
    sf::Vector2f max { 0.f, 0.f };
    sf::Vector2f size { 0.f, 0.f };

    void setPosition(sf::Vector2f pos)
    {
        left = pos.x;
        top = pos.y;
        min = pos;
        max = min + size;
    }

    void setSize(sf::Vector2f size)
    {
        this->size = size;
        width = size.x;
        height = size.y;
        max = min + size;
    }

    void move(sf::Vector2f offset)
    {
        left += offset.x;
        top += offset.y;
        min += offset;
        max += offset;
    }

    Collision_Rect() = default;
    Collision_Rect(sf::FloatRect r)
    {
        setPosition(sf::Vector2f(r.left, r.top));
        setSize(sf::Vector2f(r.width, r.height));
    }
};
