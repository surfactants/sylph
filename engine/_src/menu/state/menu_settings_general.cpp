#include <menu/state/menu_settings_general.hpp>

Menu_Settings_General::Menu_Settings_General()
{
    nav.push_back(Button(std::string("save"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("default"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(&Menu::escape, this), csize));

    setEscape(Menu::SETTINGS);

    placeNav();

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;

    check_boxes.push_back(Check_Box(*font, "lorem ipsum", 48));

    for (auto& cb : check_boxes) {
        cb.setPosition(pos);
        pos.y += 96.f;
        elements.push_back(&cb);
    }
}

void Menu_Settings_General::enterState()
{}

void Menu_Settings_General::exitState()
{}
