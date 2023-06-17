#include <ui/menu/menu_title.hpp>

Menu_Title::Menu_Title()
{
    addNav("new game", std::bind(setUIState, UI::NEW_GAME));
    addNav("continue", std::bind(setUIState, UI::NEW_GAME));
    addNav("load game", std::bind(setUIState, UI::LOAD_GAME));
    addNav("settings", std::bind(setUIState, UI::SETTINGS));
    addNav("quit to desktop", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::QUIT);

    placeNav();
}
