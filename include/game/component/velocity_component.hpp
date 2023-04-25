#pragma once

#include <engine/math/primordial.hpp>

#include "component.hpp"

class Velocity_Component : public Component {
public:
    Velocity_Component() : Component(VELOCITY) {}

    enum State {
        STOPPED,
        ACCELERATING,
        DECELERATING
    };

    operator sf::Vector2f ()
    {
        return v;
    }

    void update(float delta_time);

    void setState(State s);
    void setAcceleration(float a);
    void setDeceleration(float d);
    void setSpeed(float s);
    void setMaxSpeed(float m);
    void setAngle(float a);

private:
    void accelerate();
    void checkMaxSpeed();

    void decelerate();
    void checkMinSpeed();

    void calculateVector();

    float acceleration { 0.f };
    float deceleration { 0.f };
    float speed { 0.f };
    float max_speed { 0.f };
    float angle { 0.f };

    sf::Vector2f v;

    State state { STOPPED };
};
