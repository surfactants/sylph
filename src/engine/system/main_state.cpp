#include <engine/system/main_state.hpp>

std::function<void(Main_State::State)> Main_State::setState;
std::function<sf::Vector2f(sf::View)> Main_State::relativeMousePos;

Main_State::Main_State()
{}

void Main_State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& drawable : drawables) {
        target.draw(*drawable, states);
    }
}
