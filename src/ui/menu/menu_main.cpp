#include <ui/menu/menu_main.hpp>

Menu_Main::Menu_Main()
{
    addNav("new game", std::bind(setUIState, UI::NEW_GAME));
    addNav("continue", std::bind(setUIState, UI::NEW_GAME));
    addNav("load game", std::bind(setUIState, UI::LOAD_GAME));
    addNav("settings", std::bind(setUIState, UI::SETTINGS));
    addNav("quit", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::QUIT);

    placeNav();
}
