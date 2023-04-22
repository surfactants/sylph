#pragma once

//#include <stdint.h>

struct Component {
    Component() = delete;
    enum Type {
        SPRITE,
        ANIMATED_SPRITE,
        VELOCITY,
        INPUT,
        HEALTH,
        INTERACT,
        DIALOGUE,
        SIZE /**< Equals number of elements, as long as it is always last. */
    };

    static uint8_t toInt(Type t)
    {
        return static_cast<uint8_t>(t);
    }
};
