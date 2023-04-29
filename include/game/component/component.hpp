#pragma once

enum class Component {
    TRANSFORM = 0,
    COLLISION_RECT,
    POLYGON_TILE,
    TILE,
    SIZE
};

constexpr unsigned int MAX_COMPONENTS { static_cast<unsigned int>(Component::SIZE) };

inline unsigned int toInt(Component c)
{
    return static_cast<unsigned int>(c);
}

inline Component toComponent(unsigned int i)
{
    if (i >= MAX_COMPONENTS) {
        // log this
        return Component::SIZE;
    }
    return static_cast<Component>(i);
}
