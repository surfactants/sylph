#pragma once

#include "hud.hpp"

class Player_Turn : public HUD {
public:
    Player_Turn();

    void nextTurn();

    virtual void enterState() override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

private:
    std::shared_ptr<Button> next_turn;
};
