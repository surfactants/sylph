#pragma once

#include <SFML/System/Clock.hpp>

#include "game.hpp"

class Game_Simulate : public Game {
public:
    Game_Simulate() = default;

    virtual void update(const float delta_time) override;

    static std::function<void(const Date&)> updateDate;
    static std::function<void(const Resource&)> updateResourcePanel;

private:
    sf::Clock step_timer;
    constexpr static float step_length { 1.f };

    void step();
};
