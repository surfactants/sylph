#include <engine/shell/quit_state.hpp>

Quit_State::Quit_State(sf::RenderWindow& window)
    : window { window }
{}

void Quit_State::update(const float)
{
    window.close();
}
