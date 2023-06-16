#include <engine/shell/main_state_machine.hpp>

#include <engine/shell/menu_state.hpp>
#include <engine/shell/game_state.hpp>
#include <engine/shell/quit_state.hpp>

Main_State_Machine::Main_State_Machine(sf::RenderWindow& window, Event_Bus& event_bus, Audio& audio)
{
    Main_State::setState = std::bind(&setState, this, std::placeholders::_1);

    auto open_pause = [&]() {
        setState(Main_State::MENU);
        static_cast<Menu_State*>(states[Main_State::MENU].get())->setState(Menu::PAUSE);
    };

    states[Main_State::GAME] = std::make_unique<Game_State>(open_pause);

    states[Main_State::GAME]->windowResize(window.getSize());

    Menu::setMainState = Main_State::setState;

    states[Main_State::MENU] = std::make_unique<Menu_State>(audio, static_cast<Game_State*>(states[Main_State::GAME].get()));

    states[Main_State::QUIT] = std::make_unique<Quit_State>(window);

    state = states[Main_State::MENU].get();
}

void Main_State_Machine::handleInput(const sf::Event& event)
{
    state->handleInput(event);
}

void Main_State_Machine::update(const float delta_time)
{
    state->update(delta_time);
}

void Main_State_Machine::setState(Main_State::State new_state)
{
    last_state = current_state;
    current_state = new_state;
    state = states[new_state].get();
}


void Main_State_Machine::windowResize(const sf::Vector2u& w_size)
{
    for (auto& state : states) {
        if (state.second) {
            state.second->windowResize(w_size);
        }
    }
}

void Main_State_Machine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*state, states);
}
