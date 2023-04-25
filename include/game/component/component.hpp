#pragma once

/// Component ///
/// \brief abstract, NON-POLYMORPHIC base class
/// inherited types must initialize the Type object
class Component {
public:
    enum Type {
        MOUSE_INPUT = 0,
        KEY_INPUT,
        ANIMATED_SPRITE,
        VELOCITY,
        COLLISION,
        HEALTH,
        INTERACT,
        DIALOGUE,
        SIZE /**< Equals number of elements, as long as it is always last. */
    };

    Component(const Type t) : type { t } {}

    const Type type;

    static int toInt(Type t)
    {
        return static_cast<int>(t);
    }

    int toInt()
    {
        return static_cast<int>(type);
    }
};
