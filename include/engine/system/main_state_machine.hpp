#pragma once

#include <map>
#include <memory>

#include <engine/audio/audio.hpp>
#include <engine/event/event_bus.hpp>

#include "main_state.hpp"

class Main_State_Machine : public sf::Drawable {
public:
    Main_State_Machine(sf::RenderWindow& window, Event_Bus& event_bus, Audio& audio);

    void update(float delta_time);
    void handleInput(const sf::Event& event);

    Main_State* state;

    std::map<Main_State::State, std::unique_ptr<Main_State>> states;

    Main_State::State current_state { Main_State::MENU };
    Main_State::State last_state { Main_State::QUIT };

    void setState(Main_State::State new_state);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
