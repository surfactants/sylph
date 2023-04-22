#include <engine/system/quit_state.hpp>

Quit_State::Quit_State(sf::RenderWindow& window)
    : window { window }
{
}

void Quit_State::update(float delta_time)
{
    window.close();
}

void Quit_State::handleInput(const sf::Event& event)
{
}
