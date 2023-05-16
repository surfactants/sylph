#pragma once

enum class Component {
    //ENTITY_INFO = 0,
    //COLOR,
    TRANSFORM = 0,
    COLLISION_RECT,
    POLYGON_TILE,
    HIERARCHY,
    TILE,
    ENTITY_DATA,
    BODY_INFO,
    EMPIRE_DATA,
    SIZE // gets total number of components
};

using Component_Type = short unsigned int;

constexpr Component_Type MAX_COMPONENTS { static_cast<Component_Type>(Component::SIZE) };

inline Component_Type toInt(Component c)
{
    return static_cast<Component_Type>(c);
}

inline Component toComponent(Component_Type i)
{
    if (i >= MAX_COMPONENTS) {
        // log this
        return Component::SIZE;
    }
    return static_cast<Component>(i);
}
