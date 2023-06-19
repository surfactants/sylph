#pragma once

#include "hud.hpp"

class Player_Turn : public HUD {
public:
    Player_Turn();

    void nextTurn();

private:
    Button next_turn;
};
