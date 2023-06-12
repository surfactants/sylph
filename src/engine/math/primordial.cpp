#include <engine/math/primordial.hpp>

int roundFloat(float f)
{
    return static_cast<int>(f + (sign(f) / 2.f));
}

sf::Vector2f calculateMoveVector(float angle, float velocity)
{
    sf::Vector2f v;
    angle -= 90;
    angle *= (PI / 180); //converts angle to radians

    v.x = velocity * cos(angle);
    v.y = velocity * sin(angle);
    return v;
}
