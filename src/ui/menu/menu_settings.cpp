#include <ui/menu/menu_settings.hpp>

Menu_Settings::Menu_Settings()
{
    addNav("game", std::bind(setUIState, UI::SETTINGS_GAME));
    addNav("general", std::bind(setUIState, UI::SETTINGS_GENERAL));
    addNav("audio", std::bind(setUIState, UI::SETTINGS_AUDIO));
    addNav("controls", std::bind(setUIState, UI::SETTINGS_KEYMAPPER));
    addNav("back", std::bind(&UI::escape, this));

    setEscape(UI::SETTINGS);

    placeNav();
}
