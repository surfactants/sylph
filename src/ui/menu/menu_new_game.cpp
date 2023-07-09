#include <ui/menu/menu_new_game.hpp>

#include <game/state/new_game.hpp>

Menu_New_Game::Menu_New_Game(std::function<void(New_Game_Data)> start_game)
    : start_game { start_game }
{
    addNav("BUTTON_START", std::bind(confirm, this), Element::UNAVAILABLE);
    addNav("BUTTON_CANCEL", std::bind(cancel, this));

    setEscape(UI::TITLE);

    placeNav();

    // PANEL CREATION

    const sf::Vector2f tab_size(96.f, 870.f);
    const sf::Vector2f panel_size(1300.f, tab_size.y);

    const sf::Vector2f tab_pos = nav.front()->getPosition() + sf::Vector2f(392.f, 0.f);
    const sf::Vector2f panel_pos = tab_pos + sf::Vector2f(tab_size.x, 0.f);
    panels = std::make_unique<Tabbed_Panel>();
    panels->setPosition(tab_pos);
    panels->setSize(tab_size);

    species = std::make_shared<Species_Panel>(*font, panel_pos, panel_size, localize);
    species->view = &view;
    home = std::make_shared<Home_Panel>(*font, panel_pos, panel_size, localize);
    home->view = &view;
    civ = std::make_shared<Civ_Panel>(*font, panel_pos, panel_size, localize);
    civ->view = &view;

    // SAVE PANELS
    panels->addPanel(species);
    panels->addPanel(home);
    panels->addPanel(civ);

    elements.push_back(panels.get());

    textboxes.push_back(species->name);
    textboxes.push_back(home->star_name);
    textboxes.push_back(home->homeworld_name);
    textboxes.push_back(civ->name);
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
    data.player_name = civ->name->getString();
    data.home_system = home->star_name->getString();
    data.homeworld = home->homeworld_name->getString();
    data.player_color = civ->color->getColor();
    start_game(data);
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::TITLE);
}
