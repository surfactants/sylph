#include <menu/state/menu_settings_audio.hpp>

Menu_Settings_Audio::Menu_Settings_Audio(Audio& audio)
{
    nav.push_back(Button(std::string("save"), *font, std::bind(save, this), csize));
    nav.push_back(Button(std::string("default"), *font, std::bind(loadDefaults, this), csize));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(&Menu::escape, this), csize));

    placeNav();

    sliders.push_back(Slider("music"));
    sliders.push_back(Slider("game"));
    sliders.push_back(Slider("ui"));

    sliders[0].fillChangeCallback = [&](float v) { audio.setMusicVolume(v); };
    sliders[1].fillChangeCallback = [&](float v) { audio.setSoundVolume(Sound::GAME, v); };
    sliders[2].fillChangeCallback = [&](float v) { audio.setSoundVolume(Sound::UI, v); };

    read = [&]()
        {
            sliders[0].setFill(audio.getMusicVolume());
            sliders[1].setFill(audio.getSoundVolume(Sound::GAME));
            sliders[2].setFill(audio.getSoundVolume(Sound::UI));
        };

    read();

    placeSliders();

    setMusicVolume = [&](float v) { audio.setMusicVolume(v); };
    setSoundVolume = [&](Sound::Source s, float v) { audio.setSoundVolume(s, v); };

    defaultCallback = std::bind(&Audio::loadDefaults, &audio);
    saveToDatabase = std::bind(&Audio::saveToDatabase, &audio);

    setEscape(Menu::SETTINGS);
}

void Menu_Settings_Audio::enterState()
{}

void Menu_Settings_Audio::exitState()
{}

void Menu_Settings_Audio::save()
{
    for (auto& slider : sliders) {
        slider.fillChangeCallback(slider.getFill());
        slider.finalize();
    }
    saveToDatabase();
    escape();
}

void Menu_Settings_Audio::loadDefaults()
{
    defaultCallback();
    read();
}

void Menu_Settings_Audio::cancel()
{
    for (auto& slider : sliders) {
        slider.fillChangeCallback(slider.revert());
    }
    escape();
}
