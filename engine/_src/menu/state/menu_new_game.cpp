#include <menu/state/menu_new_game.hpp>

Menu_New_Game::Menu_New_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    nav.push_back(Button(std::string("start"), *font, std::bind(setMainState, Main_State::GAME), csize));
    //nav.back().unsetAvailable();
    nav.push_back(Button(std::string("cancel"), *font, std::bind(setMenuState, Menu::MAIN), csize));

    setEscape(Menu::MAIN);

    placeNav();

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;

    Simple_Textbox textbox;
    textbox.setFont(*font);
    textbox.setPosition(pos);
    textbox.clearActive = std::bind(&deactivateTextbox, this);//[&]() { active_textbox = nullptr; };
    textbox.setActive = std::bind(&activateTextbox, this, std::placeholders::_1);//[&](Simple_Textbox* t) { active_textbox = t; };

    textboxes.push_back(std::move(textbox));

    for (auto& t : textboxes) {
        elements.push_back(&t);
    }
}

void Menu_New_Game::enterState()
{}

void Menu_New_Game::exitState()
{
    if (active_textbox) {
        deactivateTextbox();
    }
}

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
