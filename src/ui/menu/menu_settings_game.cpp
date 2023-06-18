#include <ui/menu/menu_settings_game.hpp>

#include <engine/database/database_settings_game.hpp>

Menu_Settings_Game::Menu_Settings_Game(std::function<void(Game_Settings)> save_settings)
    : save_to_game { save_settings }
{
    addNav("BUTTON_SAVE", std::bind(confirm, this));
    addNav("BUTTON_DEFAULT", std::bind(loadDefaults, this));
    addNav("BUTTON_CANCEL", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    std::vector<std::pair<std::string, int>> data = {
        { "zero", 0 }, { "one", 1 }, { "two", 2 }, { "three", 3 }, { "four", 4 }, { "five", 5 }
    };

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;

    dropdown_difficulty.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080));
    dropdown_difficulty.load(data, *font, 32, 0);

    pos.y += 256.f;

    data.erase(data.begin());

    dropdown_speed.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080));
    dropdown_speed.load(data, *font, 32, 0);

    // dropdowns go last, in reverse vertical order, to ensure proper layering
    elements.push_back(&dropdown_speed);
    elements.push_back(&dropdown_difficulty);

    load();

    Game_Settings s;
    s.difficulty = dropdown_difficulty.selected();
    s.speed = dropdown_speed.selected();
    save_to_game(s);
}

void Menu_Settings_Game::enterState()
{
    load();
}

void Menu_Settings_Game::load()
{
    Database_Settings_Game db;
    Game_Settings s = db.read();
    dropdown_difficulty.set(s.difficulty);
    dropdown_speed.set(s.speed);
}

void Menu_Settings_Game::loadDefaults()
{
    Database_Settings_Game db;
    Game_Settings s = db.readDefaults();
    dropdown_difficulty.set(s.difficulty);
    dropdown_speed.set(s.speed);
}

void Menu_Settings_Game::confirm()
{
    // package settings
    Game_Settings s;
    s.difficulty = dropdown_difficulty.selected();
    s.speed = dropdown_speed.selected();

    // save to database
    Database_Settings_Game db;
    db.write(s);

    // game callback

    save_to_game(s);

    //escape();
}
