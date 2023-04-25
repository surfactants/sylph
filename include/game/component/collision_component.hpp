#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>

#include "component.hpp"

/// Collision Component ///
/// \brief basic floatrect collision
class Collision_Component : public Component {
public:
    Collision_Component();

    template <typename T>
    bool contains(sf::Vector2<T> v)
    {
        return bounds.contains(v.x, v.y);
    }

    bool intersects(sf::FloatRect r);

    void set(sf::FloatRect b);

    void move(sf::Vector2f offset);

private:
    sf::FloatRect bounds;
};
