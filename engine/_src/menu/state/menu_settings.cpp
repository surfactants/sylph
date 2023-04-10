#include <menu/state/menu_settings.hpp>

Menu_Settings::Menu_Settings()
{
    nav.push_back(Button(std::string("general"), *font, std::bind(setMenuState, Menu::SETTINGS_GENERAL), csize));
    nav.push_back(Button(std::string("audio"), *font, std::bind(setMenuState, Menu::SETTINGS_AUDIO), csize));
    nav.push_back(Button(std::string("controls"), *font, std::bind(setMenuState, Menu::SETTINGS_KEYMAPPER), csize));
    nav.push_back(Button(std::string("back"), *font, std::bind(&Menu::escape, this), csize));

    setEscape(Menu::SETTINGS);

    placeNav();
}

void Menu_Settings::enterState()
{
    Menu::enterState();
}

void Menu_Settings::exitState()
{
    Menu::exitState();
}
