#pragma once

#include <SFML/System/Vector2.hpp>

///////////////////////////////////
// TODO:
// - This class needs to be genericized to work with collision as well!
// - > (currently, it only works for an rts-type wasd parser)
//

/// ACCELERATOR ///
/// \brief Reads motion-based player input
///
class Accelerator {
public:
    Accelerator();
    sf::Vector2f update(float delta_time);

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

private:
    bool up { false };
    bool left { false };
    bool right { false };
    bool down { false };

    sf::Vector2f m_velocity { 0.f, 0.f };

    float speed { 0.f };
    float max_speed { 0.f };
    float acceleration { 0.f };
    float deceleration { 5.f };
};
