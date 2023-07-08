#include <ui/menu/menu_new_game.hpp>

#include <game/state/new_game.hpp>

Menu_New_Game::Menu_New_Game(std::function<void(New_Game_Data)> start_game)
    : start_game { start_game }
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("BUTTON_START", std::bind(confirm, this), Element::UNAVAILABLE);
    addNav("BUTTON_CANCEL", std::bind(cancel, this));

    setEscape(UI::TITLE);

    placeNav();

    const sf::Vector2f tbox_size(512.f, 96.f);

    std::string text;
    std::string loc;

    const sf::Vector2f tab_size(96.f, 870.f);
    const sf::Vector2f panel_size(1300.f, tab_size.y);

    const sf::Vector2f tab_pos = nav.front()->getPosition() + sf::Vector2f(392.f, 0.f);
    const sf::Vector2f panel_pos = tab_pos + sf::Vector2f(tab_size.x, 0.f);

    const unsigned int elem_csize { 32 };
    const unsigned int title_csize { 48 };

    // TABBED PANELS
    panels = std::make_unique<Tabbed_Panel>();
    panels->setPosition(tab_pos);
    panels->setSize(tab_size);

    // SPECIES PANEL
    species_panel = std::make_shared<Panel>(panel_pos, panel_size);

    // title
    text = "SPECIES_TITLE";
    loc = localize(text);
    species_title = std::make_shared<sf::Text>(loc, *font, title_csize);
    localize.recordPersistent(text, species_title.get());
    species_panel->addText(species_title.get(), Panel::LEFT, panel_size.x);

    // elements
    tbox_species_name = std::make_shared<Simple_Textbox>("SPECIES_NAME", *font, elem_csize);
    tbox_species_name->setSize(tbox_size);
    species_panel->addElement(tbox_species_name.get(), Panel::LEFT);

    // HOME PANEL
    home_panel = std::make_shared<Panel>(panel_pos, panel_size);

    // title
    text = "HOME_TITLE";
    loc = localize(text);
    home_title = std::make_shared<sf::Text>(loc, *font, title_csize);
    localize.recordPersistent(text, home_title.get());
    home_panel->addText(home_title.get(), Panel::LEFT, panel_size.x);

    // elements
    tbox_star_name = std::make_shared<Simple_Textbox>("STAR_NAME", *font, elem_csize);
    tbox_star_name->setSize(tbox_size);
    home_panel->addElement(tbox_star_name.get(), Panel::LEFT);

    tbox_homeworld_name = std::make_shared<Simple_Textbox>("HOMEWORLD_NAME", *font, elem_csize);
    tbox_homeworld_name->setSize(tbox_size);
    home_panel->addElement(tbox_homeworld_name.get(), Panel::LEFT);

    // CIV PANEL
    civ_panel = std::make_shared<Panel>(panel_pos, panel_size);

    // title
    text = "CIV_TITLE";
    loc = localize(text);
    civ_title = std::make_shared<sf::Text>(loc, *font, title_csize);
    localize.recordPersistent(text, civ_title.get());
    civ_panel->addText(civ_title.get(), Panel::LEFT, panel_size.x);

    // elements
    tbox_civ_name = std::make_shared<Simple_Textbox>("CIVILIZATION_NAME", *font, elem_csize);
    tbox_civ_name->setSize(tbox_size);
    civ_panel->addElement(tbox_civ_name.get(), Panel::LEFT);

    civ_color = std::make_shared<Color_Selector>("COLOR", *font);
    civ_panel->addElement(civ_color.get(), Panel::RIGHT);

    // SAVE PANELS
    panels->addPanel(species_panel);
    panels->addPanel(home_panel);
    panels->addPanel(civ_panel);

    elements.push_back(panels.get());

    textboxes.push_back(tbox_species_name);
    textboxes.push_back(tbox_star_name);
    textboxes.push_back(tbox_homeworld_name);
    textboxes.push_back(tbox_civ_name);
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
    for (auto& t : textboxes) {
        t->clear();
    }
    civ_color->reset();
}

void Menu_New_Game::confirm()
{
    // initiate game loading
    New_Game_Data data;
    data.player_name = tbox_civ_name->getString();
    data.home_system = tbox_star_name->getString();
    data.homeworld = tbox_homeworld_name->getString();
    data.player_color = civ_color->getColor();
    start_game(data);
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::TITLE);
}
