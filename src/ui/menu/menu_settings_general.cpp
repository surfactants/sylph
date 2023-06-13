#include <ui/menu/menu_settings_general.hpp>

std::function<void(sf::Vector2u)> Menu_Settings_General::resizeWindow;

Menu_Settings_General::Menu_Settings_General()
{
    addNav("save", std::bind(confirm, this));
    addNav("default", []() {});
    addNav("cancel", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    std::vector<std::pair<std::string, sf::Vector2u>> data = {
        { "1920x1080", sf::Vector2u(1920, 1080) },
        { "1600x900", sf::Vector2u(1600, 900) },
        { "1366x768", sf::Vector2u(1366, 768) },
        { "1280x720", sf::Vector2u(1280, 720) },
        { "1024x576", sf::Vector2u(1024, 576) }
    }; // currently all 16:9, will add something for aspect ratios...

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;

    window_resizer.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080));
    window_resizer.load(data, *font, 32, 0);

    pos.y += 128.f;

    check_boxes.push_back(Check_Box(*font, "lorem ipsum", 48));

    for (auto& cb : check_boxes) {
        cb.setPosition(pos);
        pos.y += 96.f;
        elements.push_back(&cb);
    }

    elements.push_back(&window_resizer); // drop down goes last so it properly overlays other elements
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
    escape();
}
