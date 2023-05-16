#include <menu/state/menu_new_game.hpp>

#include <game/state/new_game.hpp>

Menu_New_Game::Menu_New_Game(std::function<void(New_Game_Data)> start_game)
    : start_game { start_game }
{
    // textboxes, color pickers, buttons, checkboxes, sliders

    addNav("start", std::bind(start, this), Menu_Element::UNAVAILABLE);
    addNav("cancel", std::bind(cancel, this));

    setEscape(Menu::MAIN);

    placeNav();

    sf::Vector2f size(512.f, 96.f);

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;

    Simple_Textbox textbox;
    textbox.setFont(*font);
    textbox.setPosition(pos);
    textbox.setSize(size);

    textboxes.push_back(std::move(textbox));

    for (auto& t : textboxes) {
        elements.push_back(&t);
    }

    pos.y += 128.f;

    Color_Selector selector("empire color", *font);
    selector.setPreview(pos, sf::Vector2f(96.f, 64.f));

    sf::Vector2f selector_pos(pos);
    selector_pos.x += textboxes.front().getSize().x + 128.f;
    selector_pos.y = textboxes.front().getPosition().y;
    selector.setPosition(selector_pos);

    selectors.push_back(std::move(selector));

    pos.y += 128.f;

    selector = Color_Selector();
    selector.setPreview(pos, sf::Vector2f(96.f, 64.f));

    selector_pos = pos;
    selector_pos.x += textboxes.front().getSize().x + 128.f;
    selector_pos.y = textboxes.front().getPosition().y + 128.f;
    selector.setPosition(selector_pos);

    selectors.push_back(std::move(selector));

    for (auto& s : selectors) {
        elements.push_back(&s);
    }
}

void Menu_New_Game::handleInput(const sf::Event& event)
{
    Menu::handleInput(event);
    if (validate()) {
        if (!valid) {
            valid = true;
            nav.front().setState(Menu_Element::READY);
        }
    }
    else if (valid) {
        valid = false;
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

void Menu_New_Game::exitState()
{
    for (auto& t : textboxes) {
        t.clear();
    }
    for (auto& s : selectors) {
        s.deactivate();
    }
}

void Menu_New_Game::start()
{
    // initiate game loading
    New_Game_Data data;
    data.player_name = textboxes.front().getString();
    data.player_color = selectors.front().getColor();
    start_game(data);
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setMenuState(Menu::MAIN);
}
