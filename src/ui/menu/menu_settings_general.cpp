#include <ui/menu/menu_settings_general.hpp>

#include <engine/database/database_settings_general.hpp>

std::function<void(sf::Vector2u)> Menu_Settings_General::resizeWindow;

Menu_Settings_General::Menu_Settings_General()
{
    addNav("BUTTON_SAVE", std::bind(confirm, this));
    addNav("BUTTON_DEFAULT", []() {});
    addNav("BUTTON_CANCEL", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    std::vector<std::pair<std::string, sf::Vector2u>> vdata = {
        { "1920x1080", sf::Vector2u(1920, 1080) },
        { "1600x900", sf::Vector2u(1600, 900) },
        { "1366x768", sf::Vector2u(1366, 768) },
        { "1280x720", sf::Vector2u(1280, 720) },
        { "1024x576", sf::Vector2u(1024, 576) }
    }; // currently all 16:9, will add something for aspect ratios...

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 512.f;

    window_resizer.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080)); //TODO
    window_resizer.load(vdata, *font, 32, 0);

    pos.y += 128.f;

    std::vector<std::pair<std::string, std::string>> data = {
        { "ENGLISH", "EN" },
        { "ESPAÑOL", "ES" },
    };

    language_selector.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080)); //TODO
    language_selector.load(data, *font, 32, 0);
    Database_Settings_General dbsg;
    language_selector.set(dbsg.activeLanguage());
/*
    check_boxes.push_back(Check_Box(*font, "lorem ipsum", 48));

    for (auto& cb : check_boxes) {
        cb.setPosition(pos);
        pos.y += 96.f;
        elements.push_back(&cb);
    }
*/
    // drop downs go last so they properly overlay other elements
    // (in ascending order so they properly overlay each other, too)
    elements.push_back(&language_selector);
    elements.push_back(&window_resizer);
}

void Menu_Settings_General::confirm()
{
    // perform database operations and invoke game callback:
    /*
    Database_Commands dbc;
    dbc.write(keymapper.getCommands());
    saveCommands(keymapper.getCommands());
    */
    resizeWindow(window_resizer.selected());
    localize.changeLanguage(language_selector.selected());
    escape();
}
