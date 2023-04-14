#include <menu/state/menu_settings.hpp>

Menu_Settings::Menu_Settings()
{
    addNav("general", std::bind(setMenuState, Menu::SETTINGS_GENERAL));
    addNav("audio", std::bind(setMenuState, Menu::SETTINGS_AUDIO));
    addNav("controls", std::bind(setMenuState, Menu::SETTINGS_KEYMAPPER));
    addNav("back", std::bind(&Menu::escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();
}
