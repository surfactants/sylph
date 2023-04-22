#pragma once

#include "primordial.hpp"

namespace collide {

bool convexShape_Point(const sf::ConvexShape& shape, const sf::Vector2f point)
{
    bool contains { false };
    size_t n = shape.getPointCount();
    for (size_t i = 0, j = n - 1; i < n; j = i++) {
        sf::Vector2f pi = shape.getPoint(i);
        sf::Vector2f pj = shape.getPoint(j);
        if (((pi.y > point.y) != (pj.y > point.y))
            && (point.x < (pj.x - pi.x) * (point.y - pi.y) / (pj.y - pi.y) + pi.x)) {
            contains = !contains;
        }
    }

    return contains;
}

}
