#pragma once

#include <map>

#include <engine/audio/audio.hpp>

#include "menu.hpp"

class Menu_Settings_Audio : public Menu {
public:
    Menu_Settings_Audio(Audio& audio);

    std::function<void(float)> setMusicVolume;
    std::function<void(Sound::Source, float)> setSoundVolume;

    std::function<void()> defaultCallback;
    std::function<void()> saveToDatabase;

    void loadDefaults();

    void save();

    void cancel();

    std::function<void()> read;

    std::vector<Slider> sliders;
};
