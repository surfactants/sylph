#pragma once

#include <SFML/System/Vector2.hpp>

#include <cmath>

constexpr static float PI { 3.14159265359 };

// basic math operations

/// scalarDistance ///
/// \brief Returns the scalar distance between two vector2 objects
/// uses sqrt, so it's pretty expensive
///
template <typename T>
T scalarDistance(const sf::Vector2<T> v, sf::Vector2<T> const w)
{
    T a = std::abs(w.x - v.x);
    T b = std::abs(w.y - v.y);
    return static_cast<T>(std::sqrt(pow(a, 2) + pow(b, 2)));
}

/// vectorDistance ///
/// \brief Returns the 2d vector distance between two 2d vectors.
///
template <typename T>
sf::Vector2<T> vectorDistance(const sf::Vector2<T> v, const sf::Vector2<T> w)
{
    return sf::Vector2<T>(w.x - v.x, w.y - v.y);
}

template <typename T>
int sign(T val)
{
    return (T(0) < val) - (val < T(0));
}

inline int roundFloat(float f)
{
    return static_cast<int>(f + (sign(f) / 2.f));
}

sf::Vector2f calculateMoveVector(float angle, float velocity);
