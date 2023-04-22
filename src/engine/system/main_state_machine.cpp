#include <engine/system/main_state_machine.hpp>

#include <engine/system/menu_state.hpp>
#include <engine/system/game_state.hpp>
#include <engine/system/quit_state.hpp>

Main_State_Machine::Main_State_Machine(sf::RenderWindow& window, Event_Bus& event_bus, Audio& audio)
{
    Main_State::setState = std::bind(&setState, this, std::placeholders::_1);

    auto open_pause = [&]() {
        setState(Main_State::MENU);
        static_cast<Menu_State*>(states[Main_State::MENU].get())->setMenuState(Menu::PAUSE);
    };
    states[Main_State::GAME] = std::make_unique<Game_State>(open_pause);

    Menu::setMainState = Main_State::setState;

    states[Main_State::MENU] = std::make_unique<Menu_State>(audio, static_cast<Game_State*>(states[Main_State::GAME].get()));

    states[Main_State::QUIT] = std::make_unique<Quit_State>(window);

    state = states[Main_State::MENU].get();
}

void Main_State_Machine::handleInput(const sf::Event& event)
{
    state->handleInput(event);
}

void Main_State_Machine::update(float delta_time)
{
    state->update(delta_time);
}

void Main_State_Machine::setState(Main_State::State new_state)
{
    last_state = current_state;
    current_state = new_state;
    state = states[new_state].get();
}

void Main_State_Machine::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*state, states);
}
