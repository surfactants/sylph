#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>

#include <SFML/System/Vector2.hpp>

#include <iostream>

/// << sf::Vector2<T> ///
/// \brief implements stream operators for sf::Vector2 types
///
template <typename T>
std::ostream& operator << (std::ostream& os, sf::Vector2<T> v)
{
    os << '(' << v.x << ", " << v.y << ')';
    return os;
}

/// << sf::Rect<T> ///
/// \brief implements stream operators for sf::Rect types
///
template <typename T>
inline std::ostream& operator << (std::ostream& os, sf::Rect<T> r)
{
    os << '(' << r.left << ", " << r.top << "; " << r.width << ", " << r.height << ')';
    return os;
}

inline std::ostream& operator << (std::ostream& os, sf::Color c)
{
    os << '(' << std::to_string(c.r) << ", " << std::to_string(c.g) << ", " << std::to_string(c.b) << ", " << std::to_string(c.a) << ')';
    return os;
}
