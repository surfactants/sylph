#include <menu/state/menu_load_game.hpp>

Menu_Load_Game::Menu_Load_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("load", std::bind(setMenuState, Menu::LOAD_GAME), Menu_Element::UNAVAILABLE);
    addNav("cancel", std::bind(cancel, this));

    setEscape(Main_State::QUIT);

    placeNav();
}

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
