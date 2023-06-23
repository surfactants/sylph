#pragma once

#include <SFML/Graphics/View.hpp>

#include <game/component/collision_rect.hpp>

#include "system.hpp"

class Camera_Controller : public System {
public:
    Camera_Controller();

    void update(sf::Vector2f velocity, const sf::Vector2f& mpos);

    void zoomImpulse(float delta);

    void startDrag(const sf::Vector2f& mpos);

    void endDrag(const sf::Vector2f&);

    void drag(const sf::Vector2f& mpos);

    sf::View* view { nullptr };

    Collision_Rect bounds;

    void setBounds(Collision_Rect b);

    float max_zoom { 8.f }; // scale this to world size...
    constexpr static float max_speed { 0.12f };
    constexpr static float min_zoom { 0.5f };
    constexpr static float zoom_step { 0.04f };
    constexpr static float zoom_decay { 0.002f };
    constexpr static float zoom_decay_factor { 0.025f };
    constexpr static float zoom_speed_factor { 3.f };

private:
    void move(sf::Vector2f velocity);
    void zoom();

    bool dragging { false };
    sf::Vector2f drag_pos;

    float current_zoom { 1.f };
    float zoom_speed { 0.f };
};
