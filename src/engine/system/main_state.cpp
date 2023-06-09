#include <engine/system/main_state.hpp>

std::function<void(Main_State::State)> Main_State::setState;

Main_State::Main_State()
{}

void Main_State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& drawable : drawables) {
        target.draw(*drawable, states);
    }
}
