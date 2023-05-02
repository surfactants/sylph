#include <game/system/input_accelerator.hpp>

#include <engine/math/primordial.hpp>

Input_Accelerator::Input_Accelerator()
{ }

sf::Vector2f Input_Accelerator::update(float delta_time)
{
    bool v_decay = (up == down);
    bool h_decay = (left == right);

    if (v_decay) {
        if (m_velocity.y > 0.f) {
            m_velocity.y -= deceleration;
            if (m_velocity.y < 0.f) {
                m_velocity.y = 0.f;
            }
        }
        else if (m_velocity.y < 0.f) {
            m_velocity.y += deceleration;
            if (m_velocity.y > 0.f) {
                m_velocity.y = 0.f;
            }
        }
    }
    else {
        if (up) {
            m_velocity.y -= acceleration;
        }
        if (down) {
            m_velocity.y += acceleration;
        }
    }

    if (h_decay) {
        if (m_velocity.x > 0.f) {
            m_velocity.x -= deceleration;
            if (m_velocity.x < 0.f) {
                m_velocity.x = 0.f;
            }
        }
        else if (m_velocity.x < 0.f) {
            m_velocity.x += deceleration;
            if (m_velocity.x > 0.f) {
                m_velocity.x = 0.f;
            }
        }
    }
    else {
        if (left) {
            m_velocity.x -= acceleration;
        }
        if (right) {
            m_velocity.x += acceleration;
        }
    }

    // gate at max speed
    if (std::abs(m_velocity.x) > max_speed) {
        m_velocity.x = sign(m_velocity.x) * max_speed;
    }

    if (std::abs(m_velocity.y) > max_speed) {
        m_velocity.y = sign(m_velocity.y) * max_speed;
    }

    return m_velocity;
}

void Input_Accelerator::setMaxSpeed(float speed)
{
    max_speed = speed;
}

void Input_Accelerator::setAcceleration(float acceleration)
{
    this->acceleration = acceleration;
}

void Input_Accelerator::startUp()
{
    up = true;
}

void Input_Accelerator::stopUp()
{
    up = false;
}

void Input_Accelerator::startLeft()
{
    left = true;
}

void Input_Accelerator::stopLeft()
{
    left = false;
}

void Input_Accelerator::startDown()
{
    down = true;
}

void Input_Accelerator::stopDown()
{
    down = false;
}

void Input_Accelerator::startRight()
{
    right = true;
}

void Input_Accelerator::stopRight()
{
    right = false;
}
