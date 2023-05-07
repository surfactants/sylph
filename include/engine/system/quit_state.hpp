#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "main_state.hpp"

class Quit_State : public Main_State {
public:
    Quit_State(sf::RenderWindow& window);

    virtual void update(float delta_time) override;
    virtual void handleInput(const sf::Event& event) override {}
    virtual void windowResize(const sf::Vector2u& w_size) override {}

private:
    sf::RenderWindow& window;
};
