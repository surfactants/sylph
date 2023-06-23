#pragma once

#include "hud.hpp"

class AI_Turn : public HUD {
public:
    AI_Turn();

    virtual void enterState() override;

    virtual void update(const sf::Vector2i& mpos) override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

private:
    sf::Clock clock;
    float threshold { 5.f };

    sf::Text panel_text;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
