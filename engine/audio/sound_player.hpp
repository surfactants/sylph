#pragma once

#include <SFML/Audio/Sound.hpp>

#include <deque>
#include <map>

#include <system/event/event_bus.hpp>

#include "sound.hpp"

class Sound_Player {
public:
    Sound_Player(Event_Bus& event_bus);

    void update();
    void setVolume(Sound::Source s, float vol);
    float getVolume(Sound::Source s);

    void read(Event event);

private:
    std::map<Sound::Source, float> volume;
    std::map<Event::Tag, Sound> context;
    std::deque<sf::Sound> sounds;
};
