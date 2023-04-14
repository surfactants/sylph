#include <menu/state/menu_pause.hpp>

Menu_Pause::Menu_Pause()
{
    addNav("resume", std::bind(&Menu::escape, this));
    addNav("save", std::bind(setMenuState, Menu::SAVE_GAME));
    addNav("load", std::bind(setMenuState, Menu::LOAD_GAME));
    addNav("settings", std::bind(setMenuState, Menu::SETTINGS));
    addNav("quit to main menu", [&]() { setMenuState(Menu::MAIN); Event_Bus::publish(Event::MAIN_MENU_ENTERED); });
    addNav("quit to desktop", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::GAME);

    placeNav();
}
