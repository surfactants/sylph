#include <menu/state/menu_new_game.hpp>

Menu_New_Game::Menu_New_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    nav.push_back(Button(std::string("start"), *font, std::bind(setMenuState, Menu::NEW_GAME), csize));
    nav.back().unsetAvailable();
    nav.push_back(Button(std::string("cancel"), *font, std::bind(setMenuState, Menu::LOAD_GAME), csize));

    setEscape(Main_State::QUIT);

    placeNav();
}

void Menu_New_Game::enterState()
{}

void Menu_New_Game::exitState()
{}

void Menu_New_Game::start()
{
    // initiate game loading
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setMenuState(Menu::MAIN);
}
