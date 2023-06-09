#pragma once

#include <SFML/Graphics.hpp>

#include "primordial.hpp"

namespace collide {

constexpr float POINT_EPSILON { 1.0e-4 };

inline bool convexShape_Point(const sf::ConvexShape& shape, const sf::Vector2f point)
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

inline std::pair<bool, sf::Vector2f> twoLineSegments(const sf::Vector2f& q, const sf::Vector2f& s, const sf::Vector2f& p, const sf::Vector2f& r)
{
    // https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
    std::pair<bool, sf::Vector2f> ans { false, sf::Vector2f(0.f, 0.f) };

    static auto cross = [](sf::Vector2f v, sf::Vector2f w) {
        return (v.x * w.y) - (v.y * w.x);
    };

    float rxs = cross(r, s);
    float qpxr = cross(q - p, r);

    if (fabs(rxs) < POINT_EPSILON && fabs(qpxr) < POINT_EPSILON) {
        // collinear
        return ans;
    }

    if (fabs(rxs) < POINT_EPSILON && fabs(qpxr) > POINT_EPSILON) {
        //parallel
        return ans;
    }

    float qpxs = cross(q - p, s);
    float t = qpxs / rxs;
    float u = qpxr / rxs;

    if (fabs(rxs) > POINT_EPSILON && (t >= POINT_EPSILON && t <= 1.f) && (u >= POINT_EPSILON && u <= 1.f)) {
        // intersects!
        ans.first = true;
        ans.second = sf::Vector2f(q + (u * s));
    }

    return ans;
}

inline bool contains(const sf::CircleShape& c, const sf::Vector2f& p)
{
    return (scalarDistance(c.getPosition(), p) <= c.getRadius());
}

} // namespace collide
