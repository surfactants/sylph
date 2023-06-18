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

    sf::Vector2f size(512.f, 96.f);

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;

    std::vector<std::string> tbox_names = {
        "civilization name",
        "home system name",
        "homeworld name",
        "species name"
    };

    for (const auto& name : tbox_names) {
        Simple_Textbox textbox(name);
        textbox.setFont(*font);
        textbox.setPosition(pos);
        textbox.setSize(size);
        textboxes.push_back(std::move(textbox));
        pos.y += size.y + 128.f;
    }

    int i = 0;
    for (auto& t : textboxes) {
        elements.push_back(&t);
    }

    pos = textboxes.front().getPosition();
    pos.x += 512.f + 64.f;

    sf::Vector2f preview_size(96.f, 64.f);

    Color_Selector selector("civilization color", *font);
    selector.setPreview(pos, preview_size);

    sf::Vector2f selector_pos(pos);
    selector_pos.x += preview_size.x + 192.f;
    selector_pos.y = textboxes.front().getPosition().y;
    selector.setPosition(selector_pos);

    selectors.push_back(std::move(selector));

    for (auto& s : selectors) {
        elements.push_back(&s);
    }
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

void Menu_New_Game::confirm()
{
    // initiate game loading
    New_Game_Data data;
    data.player_name = textboxes[0].getString();
    data.home_system = textboxes[1].getString();
    data.homeworld = textboxes[2].getString();
    data.player_color = selectors.front().getColor();
    start_game(data);
    setMainState(Main_State::GAME);
    Event_Bus::publish(Event(Event::MAIN_MENU_EXITED));
}

void Menu_New_Game::cancel()
{
    // reset values and return to main menu
    setUIState(UI::TITLE);
}
