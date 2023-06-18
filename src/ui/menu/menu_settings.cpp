#include <ui/menu/menu_settings.hpp>

Menu_Settings::Menu_Settings()
{
    addNav("BUTTON_GAME_SETTINGS", std::bind(setUIState, UI::SETTINGS_GAME));
    addNav("BUTTON_GENERAL_SETTINGS", std::bind(setUIState, UI::SETTINGS_GENERAL));
    addNav("BUTTON_AUDIO_SETTINGS", std::bind(setUIState, UI::SETTINGS_AUDIO));
    addNav("BUTTON_CONTROLS_SETTINGS", std::bind(setUIState, UI::SETTINGS_KEYMAPPER));
    addNav("BUTTON_BACK", std::bind(&UI::escape, this));

    setEscape(UI::SETTINGS);

    placeNav();
}
