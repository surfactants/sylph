#include <system/main_state/menu_state.hpp>

#include <menu/state/menu_main.hpp>
#include <menu/state/menu_pause.hpp>
#include <menu/state/menu_settings.hpp>
#include <menu/state/menu_settings_general.hpp>
#include <menu/state/menu_settings_audio.hpp>
#include <menu/state/menu_settings_keymapper.hpp>

Menu_State::Menu_State(Audio& audio)
{
    Menu::setMenuState = std::bind(setMenuState, this, std::placeholders::_1);

    menus[Menu::MAIN] = std::make_unique<Menu_Main>();
    menus[Menu::PAUSE] = std::make_unique<Menu_Pause>();
    menus[Menu::SETTINGS] = std::make_unique<Menu_Settings>();
    menus[Menu::SETTINGS_GENERAL] = std::make_unique<Menu_Settings_General>();
    menus[Menu::SETTINGS_AUDIO] = std::make_unique<Menu_Settings_Audio>(audio);
    menus[Menu::SETTINGS_KEYMAPPER] = std::make_unique<Menu_Settings_Keymapper>();

    menu = menus[Menu::MAIN].get();
    drawables.push_back(menu);
}

void Menu_State::update(float delta_time)
{
    menu->update();
}

void Menu_State::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        menu->clickLeft();
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        menu->releaseLeft();
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            menu->escape();
        }
    }
}

void Menu_State::setMenuState(Menu::State new_menu)
{
    menu->exitState();
    menu = menus[new_menu].get();
    menu->enterState();
    drawables[0] = menu;
    if (new_menu == Menu::SETTINGS && current_menu <= Menu::PAUSE) {
        menu->setEscape(current_menu);
    }
    last_menu = current_menu;
    current_menu = new_menu;
}
