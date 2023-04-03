#include <menu/state/menu_main.hpp>

Menu_Main::Menu_Main()
{
    auto switch_to_game = [&]()
        {
            setMainState(Main_State::GAME);
            Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
        };
    nav.push_back(Button(std::string("new game"), *font, switch_to_game, csize));
    nav.push_back(Button(std::string("load game"), *font, switch_to_game, csize));
    nav.push_back(Button(std::string("settings"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("quit"), *font, std::bind(setMainState, Main_State::QUIT), csize));

    setEscape(Main_State::QUIT);

    placeNav();
}

void Menu_Main::enterState()
{}

void Menu_Main::exitState()
{}
