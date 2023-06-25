#pragma once

#include "hud.hpp"

class AI_Turn : public HUD {
public:
    AI_Turn();

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void update(const sf::Vector2i& mpos) override;

private:
    sf::Clock clock;
    float threshold { 1.f };
};
