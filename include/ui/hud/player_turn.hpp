#pragma once

#include "hud.hpp"

class Player_Turn : public HUD {
public:
    Player_Turn();

    void nextTurn();

    virtual void windowResize(const sf::Vector2u& w_size) override;

private:
    Button next_turn;
};
