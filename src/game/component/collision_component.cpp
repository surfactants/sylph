#include <game/component/collision_component.hpp>

Collision_Component::Collision_Component()
    : Component(COLLISION)
{
}

bool Collision_Component::intersects(sf::FloatRect r)
{
    return bounds.intersects(r);
}

void Collision_Component::set(sf::FloatRect b)
{
    bounds = b;
}

void Collision_Component::move(sf::Vector2f offset)
{
    bounds.left += offset.x;
    bounds.top += offset.y;
}
