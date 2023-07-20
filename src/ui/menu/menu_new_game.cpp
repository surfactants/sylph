#include <ui/menu/menu_new_game.hpp>

#include <game/state/new_game.hpp>

Menu_New_Game::Menu_New_Game(std::function<void(New_Game_Data)> start_game)
    : start_game { start_game }
{
    addNav("BUTTON_START", std::bind(confirm, this)); // , Element::UNAVAILABLE);
    addNav("BUTTON_CANCEL", std::bind(cancel, this));

    setEscape(UI::TITLE);

    placeNav();

    // initialize Tabbed_Panel
    const sf::Vector2f tab_size(96.f, 870.f);
    const sf::Vector2f tab_pos = nav.front()->getPosition() + sf::Vector2f(392.f, 0.f);

    panels = std::make_unique<Tabbed_Panel>();
    panels->setPosition(tab_pos);
    panels->setSize(tab_size);

    // initialize Panels and add them to Tabbed_Panel
    const sf::Vector2f panel_pos = tab_pos + sf::Vector2f(tab_size.x, 0.f);
    const sf::Vector2f panel_size(1300.f, tab_size.y);

    // base panel
    base = std::make_shared<Base_Panel>(*font, panel_pos, panel_size, localize);
    base->view = &view;

    textboxes.push_back(base->player_name);

    panels->addPanel(base);

    elements.push_back(panels.get());
}

bool Menu_New_Game::handleInput(const sf::Event& event)
{
    bool handled = Menu::handleInput(event);
    if (validate()) {
        if (!valid) {
            valid = true;
            nav.front()->setState(Element::READY);
        }
    }
    else if (valid) {
        valid = false;
        nav.front()->setState(Element::UNAVAILABLE);
    }
    return handled;
}

bool Menu_New_Game::keyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Tab) {
        return panels->keyPressed(key);
    }
    else {
        return UI::keyPressed(key);
    }
}

bool Menu_New_Game::validate()
{
    for (auto& t : textboxes) {
        if (t->empty()) {
            return false;
        }
    }
    return true;
}

void Menu_New_Game::exitState()
{
    panels->setTab(0);
}

void Menu_New_Game::confirm()
{
    // initiate game loading
    New_Game_Data data;
    data.player_name = base->player_name->getString();

    start_game(data);
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::TITLE);
}
