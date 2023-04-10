#include <menu/state/menu_pause.hpp>

Menu_Pause::Menu_Pause()
{
    nav.push_back(Button(std::string("resume"), *font, std::bind(&Menu::escape, this), csize));
    nav.push_back(Button(std::string("save"), *font, std::bind(setMenuState, Menu::SAVE_GAME), csize));
    nav.push_back(Button(std::string("load"), *font, std::bind(setMenuState, Menu::LOAD_GAME), csize));
    nav.push_back(Button(std::string("settings"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("quit to main menu"), *font, [&]() { setMenuState(Menu::MAIN); Event_Bus::publish(Event::MAIN_MENU_ENTERED); }, csize));
    nav.push_back(Button(std::string("quit to desktop"), *font, std::bind(setMainState, Main_State::QUIT), csize));

    setEscape(Main_State::GAME);

    placeNav();
}

void Menu_Pause::enterState()
{
    Menu::enterState();
}

void Menu_Pause::exitState()
{
    Menu::exitState();
}
