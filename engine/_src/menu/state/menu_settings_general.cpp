#include <menu/state/menu_settings_general.hpp>

Menu_Settings_General::Menu_Settings_General()
{
    addNav("save", std::bind(save, this), Menu_Element::UNAVAILABLE);
    addNav("default", [](){});
    addNav("cancel", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    std::vector<std::pair<std::string, int>> data = {
        { "one", 1 }
      , { "two", 2 }
      , { "three", 3 }
      , { "four", 4 }
      , { "five", 5 }
      , { "six", 6 }
      , { "seven", 7 }
      , { "eight", 8 }
      , { "nine", 9 }
    };

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;

    dropdown.setView(pos, sf::Vector2f(260.f, 400.f), sf::Vector2u(1920, 1080));
    dropdown.load(data, *font, 32, 0);

    pos.y += 128.f;

    check_boxes.push_back(Check_Box(*font, "lorem ipsum", 48));

    for (auto& cb : check_boxes) {
        cb.setPosition(pos);
        pos.y += 96.f;
        elements.push_back(&cb);
    }

    elements.push_back(&dropdown); // drop down goes last so it properly overlays other elements
}
