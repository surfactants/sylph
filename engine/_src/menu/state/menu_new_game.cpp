#include <menu/state/menu_new_game.hpp>

Menu_New_Game::Menu_New_Game()
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    nav.push_back(Button(std::string("start"), *font, std::bind(setMainState, Main_State::GAME), csize, Menu_Element::UNAVAILABLE));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(setMenuState, Menu::MAIN), csize));

    setEscape(Menu::MAIN);

    placeNav();

    sf::Vector2f size(512.f, 96.f);

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;

    Simple_Textbox textbox;
    textbox.setFont(*font);
    textbox.setPosition(pos);
    textbox.setSize(size);
    textbox.clearActive = std::bind(&deactivateTextbox, this);
    textbox.setActive = std::bind(&activateTextbox, this, std::placeholders::_1);

    textboxes.push_back(std::move(textbox));

    pos.y += 128.f;

    textbox = Simple_Textbox();
    textbox.setFont(*font);
    textbox.setPosition(pos);
    textbox.setSize(size);
    textbox.clearActive = std::bind(&deactivateTextbox, this);
    textbox.setActive = std::bind(&activateTextbox, this, std::placeholders::_1);

    textboxes.push_back(std::move(textbox));

    pos.y += 128.f;

    textbox = Simple_Textbox();
    textbox.setFont(*font);
    textbox.setPosition(pos);
    textbox.setSize(size);
    textbox.clearActive = std::bind(&deactivateTextbox, this);
    textbox.setActive = std::bind(&activateTextbox, this, std::placeholders::_1);

    textboxes.push_back(std::move(textbox));

    for (auto& t : textboxes) {
        elements.push_back(&t);
    }

    pos.x += textboxes.front().getSize().x + 128.f;
    pos.y = textboxes.front().getPosition().y;

    selector.setPosition(pos);

    elements.push_back(&selector);
}

void Menu_New_Game::handleInput(const sf::Event& event)
{
    Menu::handleInput(event);
    if (validate()) {
        nav.front().setState(Menu_Element::READY);
    }
    else {
        nav.front().setState(Menu_Element::UNAVAILABLE);
    }
}

bool Menu_New_Game::validate()
{
    for (auto& t : textboxes) {
        if (t.empty()) {
            return false;
        }
    }
    return true;
}

void Menu_New_Game::enterState()
{}

void Menu_New_Game::exitState()
{
    if (active_textbox) {
        deactivateTextbox();
    }
    for (auto& t : textboxes) {
        t.clear();
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
