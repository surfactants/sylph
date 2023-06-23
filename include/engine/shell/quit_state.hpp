#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "main_state.hpp"

class Quit_State : public Main_State {
public:
    Quit_State(sf::RenderWindow& window);

    virtual void update(const float) override;
    virtual void handleInput(const sf::Event&) override {}
    virtual void windowResize(const sf::Vector2u&) override {}

private:
    sf::RenderWindow& window;
};
