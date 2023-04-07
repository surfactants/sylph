#include <menu/state/menu_save_game.hpp>

Menu_Save_Game::Menu_Save_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    nav.push_back(Button(std::string("save"), *font, std::bind(setMenuState, Menu::NEW_GAME), csize, Button::UNAVAILABLE));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(setMenuState, Menu::LOAD_GAME), csize));

    setEscape(Main_State::QUIT);

    placeNav();
}

void Menu_Save_Game::enterState()
{}

void Menu_Save_Game::exitState()
{}

void Menu_Save_Game::start()
{
    // initiate game loading
    setMainState(Main_State::GAME);
}

void Menu_Save_Game::deleteSave()
{
    // re-place the save elements after this, starting from the deleted index
}

void Menu_Save_Game::cancel()
{
    // reset values and return to main menu
    setMenuState(Menu::PAUSE);
}
