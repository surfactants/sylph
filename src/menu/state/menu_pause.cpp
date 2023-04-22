#include <menu/state/menu_pause.hpp>

std::function<void()> Menu_Pause::clearGame;

Menu_Pause::Menu_Pause()
{
    addNav("resume", std::bind(&Menu::escape, this));
    addNav("save", std::bind(setMenuState, Menu::SAVE_GAME));
    addNav("load", std::bind(setMenuState, Menu::LOAD_GAME));
    addNav("settings", std::bind(setMenuState, Menu::SETTINGS));
    auto main_menu =
        [&]()
        {
            setMenuState(Menu::MAIN);
            clearGame();
            Event_Bus::publish(Event::MAIN_MENU_ENTERED);
        };
    addNav("quit to main menu", main_menu);
    addNav("quit to desktop", std::bind(setMainState, Main_State::QUIT));

    setEscape(Main_State::GAME);

    placeNav();
}
