#include <game/system/accelerator.hpp>

#include <engine/math/primordial.hpp>

#include <engine/util/sfml_stream.hpp>

Accelerator::Accelerator()
{
}

sf::Vector2f Accelerator::update(float delta_time)
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

void Accelerator::setMaxSpeed(float speed)
{
    max_speed = speed;
}

void Accelerator::setAcceleration(float acceleration)
{
    this->acceleration = acceleration;
}

void Accelerator::startUp()
{
    up = true;
}

void Accelerator::stopUp()
{
    up = false;
}

void Accelerator::startLeft()
{
    left = true;
}

void Accelerator::stopLeft()
{
    left = false;
}

void Accelerator::startDown()
{
    down = true;
}

void Accelerator::stopDown()
{
    down = false;
}

void Accelerator::startRight()
{
    right = true;
}

void Accelerator::stopRight()
{
    right = false;
}
