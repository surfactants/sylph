#include <menu/state/menu_save_game.hpp>

Menu_Save_Game::Menu_Save_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("save", std::bind(setMenuState, Menu::NEW_GAME), Menu_Element::UNAVAILABLE);
    addNav("cancel", std::bind(setMenuState, Menu::LOAD_GAME));

    setEscape(Main_State::QUIT);

    placeNav();
}

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
