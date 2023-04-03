#include <menu/state/menu_settings_general.hpp>

Menu_Settings_General::Menu_Settings_General()
{
    nav.push_back(Button(std::string("save"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("default"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(&Menu::escape, this), csize));

    setEscape(Menu::SETTINGS);

    placeNav();
}

void Menu_Settings_General::enterState()
{}

void Menu_Settings_General::exitState()
{}
