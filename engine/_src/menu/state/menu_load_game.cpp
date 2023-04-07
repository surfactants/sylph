#include <menu/state/menu_load_game.hpp>

Menu_Load_Game::Menu_Load_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    nav.push_back(Button(std::string("start"), *font, std::bind(setMenuState, Menu::NEW_GAME), csize, Button::UNAVAILABLE));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(cancel, this), csize));

    setEscape(Main_State::QUIT);

    placeNav();
}

void Menu_Load_Game::enterState()
{}

void Menu_Load_Game::exitState()
{}

void Menu_Load_Game::start()
{
    // initiate game loading
    setMainState(Main_State::GAME);
}

void Menu_Load_Game::deleteSave()
{
    // re-place the save elements after this, starting from the deleted index
}

void Menu_Load_Game::cancel()
{
    // reset values and return to main menu
    escape();
}
