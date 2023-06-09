#include <menu/state/menu_main.hpp>

Menu_Main::Menu_Main()
{
    addNav("new game", std::bind(setMenuState, Menu::NEW_GAME));
    addNav("continue", std::bind(setMenuState, Menu::NEW_GAME));
    addNav("load game", std::bind(setMenuState, Menu::LOAD_GAME));
    addNav("settings", std::bind(setMenuState, Menu::SETTINGS));
    addNav("quit", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::QUIT);

    placeNav();
}
