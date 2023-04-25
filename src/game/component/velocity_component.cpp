#include <game/component/velocity_component.hpp>

void Velocity_Component::update(float delta_time)
{
    switch (state) {
        case STOPPED:
            break;
        case ACCELERATING:
            accelerate();
            break;
        case DECELERATING:
            decelerate();
            break;
    }
}

void Velocity_Component::setAcceleration(float a)
{
    acceleration = a;
}

void Velocity_Component::setDeceleration(float a)
{
    acceleration = a;
}

void Velocity_Component::setSpeed(float s)
{
    speed = s;
}

void Velocity_Component::setMaxSpeed(float m)
{
    max_speed = m;
    checkMaxSpeed();
}

void Velocity_Component::setAngle(float a)
{
    angle = a;
    calculateVector();
}

void Velocity_Component::accelerate()
{
    speed += acceleration;
    checkMaxSpeed();
    calculateVector();
}

void Velocity_Component::checkMaxSpeed()
{
    if (speed > max_speed) {
        speed = max_speed;
    }
}

void Velocity_Component::decelerate()
{
    speed -= deceleration;
    checkMinSpeed();
    calculateVector();
}

void Velocity_Component::checkMinSpeed()
{
    if (speed < 0.f) {
        speed = 0.f;
    }
}

void Velocity_Component::calculateVector()
{
    v = calculateMoveVector(angle, speed);
}
