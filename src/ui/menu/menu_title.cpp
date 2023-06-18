#include <ui/menu/menu_title.hpp>

Menu_Title::Menu_Title()
{
    addNav("BUTTON_NEW_GAME", std::bind(setUIState, UI::NEW_GAME));
    addNav("BUTTON_CONTINUE", std::bind(setUIState, UI::NEW_GAME));
    addNav("BUTTON_LOAD", std::bind(setUIState, UI::LOAD_GAME));
    addNav("BUTTON_SETTINGS", std::bind(setUIState, UI::SETTINGS));
    addNav("BUTTON_QUIT_TO_DESKTOP", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::QUIT);

    placeNav();
}
