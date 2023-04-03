#include <system/main_state/main_state.hpp>

std::function<void(Main_State::State)> Main_State::setState;

void Main_State::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& drawable : drawables) {
        target.draw(*drawable, states);
    }
}
