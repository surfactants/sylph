#pragma once

#include <engine/event/event_bus.hpp>

#include "music_player.hpp"
#include "sound_player.hpp"

class Audio {
public:
    Audio(Event_Bus& event_bus);

    void update();

    void setMusicVolume(float vol);
    float getMusicVolume();

    void setSoundVolume(Sound::Source s, float vol);
    float getSoundVolume(Sound::Source s);

    void loadDefaults();
    void load(bool default_vol = false);
    void saveToDatabase();

private:
    Music_Player music;
    Sound_Player sound;
};
