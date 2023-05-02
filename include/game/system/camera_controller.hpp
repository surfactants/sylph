#pragma once

#include <SFML/Graphics/View.hpp>

#include <game/component/collision_rect.hpp>

#include "system.hpp"

class Camera_Controller : public System {
public:
    Camera_Controller() = default;

    void update(sf::Vector2f velocity);

    void zoom(float delta);

    sf::View* view { nullptr };

    Collision_Rect bounds;

    float current_zoom { 1.f };
    float max_zoom { 4.f };
    float min_zoom { 0.5f };
    float zoom_step { 0.1f };
    constexpr static float zoom_speed_factor { 3.f };
};
