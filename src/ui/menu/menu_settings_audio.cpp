#include <ui/menu/menu_settings_audio.hpp>

Menu_Settings_Audio::Menu_Settings_Audio(Audio& audio)
{
    addNav("BUTTON_SAVE", std::bind(save, this));
    addNav("BUTTON_DEFAULT", std::bind(loadDefaults, this));
    addNav("BUTTON_CANCEL", std::bind(cancel, this));

    placeNav();

    sliders.push_back(Slider("music"));
    sliders.push_back(Slider("game"));
    sliders.push_back(Slider("ui"));

    sliders[0].fillChangeCallback = [&](float v) { audio.setMusicVolume(v); };
    sliders[1].fillChangeCallback = [&](float v) { audio.setSoundVolume(Sound::GAME, v); };
    sliders[2].fillChangeCallback = [&](float v) { audio.setSoundVolume(Sound::UI, v); };

    read = [&]() {
        sliders[0].setFill(audio.getMusicVolume());
        sliders[1].setFill(audio.getSoundVolume(Sound::GAME));
        sliders[2].setFill(audio.getSoundVolume(Sound::UI));
    };

    read();

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;

    for (auto& slider : sliders) {
        slider.set(pos, *font);
        pos.y += slider_offset;

        slider.finalize();
        elements.push_back(&slider);
    }

    setMusicVolume = [&](float v) { audio.setMusicVolume(v); };
    setSoundVolume = [&](Sound::Source s, float v) { audio.setSoundVolume(s, v); };

    defaultCallback = std::bind(&Audio::loadDefaults, &audio);
    saveToDatabase = std::bind(&Audio::saveToDatabase, &audio);

    setEscape(Menu::SETTINGS);
}

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
