#include <menu/state/menu_main.hpp>

Menu_Main::Menu_Main()
{
    nav.push_back(Button(std::string("new game"), *font, std::bind(setMenuState, Menu::NEW_GAME), csize));
    nav.push_back(Button(std::string("load game"), *font, std::bind(setMenuState, Menu::LOAD_GAME), csize));
    nav.push_back(Button(std::string("settings"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("quit"), *font, std::bind(setMainState, Main_State::QUIT), csize));

    setEscape(Main_State::QUIT);

    placeNav();
}

void Menu_Main::enterState()
{
    Menu::enterState();
}

void Menu_Main::exitState()
{
    Menu::exitState();
}
