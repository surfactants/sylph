#pragma once

#include "hud.hpp"

class HUD_Simulate : public HUD {
public:
    HUD_Simulate();

    virtual void enterState() override;
    virtual void exitState() override;

private:
    sf::Clock clock;
    float threshold { 5.f };
};
