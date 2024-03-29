#pragma once

#include <SFML/System/Vector2.hpp>

/// INPUT ACCELERATOR ///
/// \brief Reads motion-based player input and generates a velocity vector
///
class Input_Accelerator {
public:
    Input_Accelerator() = default;
    sf::Vector2f update(const float delta_time);

    void setSpeed(float speed);
    void setMaxSpeed(float speed);
    void setAcceleration(float acceleration);

    void startUp();
    void stopUp();
    void startLeft();
    void stopLeft();
    void startDown();
    void stopDown();
    void startRight();
    void stopRight();

    sf::Vector2f velocity()
    {
        return m_velocity;
    }

private:
    bool up    { false };
    bool left  { false };
    bool right { false };
    bool down  { false };

    sf::Vector2f m_velocity { 0.f, 0.f };

    float speed { 0.f };
    float max_speed { 0.f };
    float acceleration { 0.f };
    float deceleration { 5.f };
};
