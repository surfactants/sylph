#pragma once

#include <SFML/Graphics.hpp>

#include <engine/audio/audio.hpp>
#include <engine/event/event_bus.hpp>

#include "main_state_machine.hpp"

class Shell {
public:
    Shell();

    void run();

private:
    sf::RenderWindow window;

    sf::Event event;

    Event_Bus event_bus;

    Audio audio { event_bus };

    Main_State_Machine state { window, event_bus, audio };

    void update();

    void draw();

    sf::Text fps_text;
    sf::Clock fps_clock;
};
