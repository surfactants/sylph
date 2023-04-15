#include <engine/system/menu_state.hpp>

#include <engine/database/database_commands.hpp>

#include <menu/states.hpp>

Menu_State::Menu_State(Audio& audio, Game_State* game)
{
    Menu::setMenuState = std::bind(setMenuState, this, std::placeholders::_1);

    menus[Menu::MAIN] = std::make_unique<Menu_Main>();
    menus[Menu::PAUSE] = std::make_unique<Menu_Pause>();
    menus[Menu::SETTINGS] = std::make_unique<Menu_Settings>();

    auto saveSettings = std::bind(&Game_State::loadSettings, game, std::placeholders::_1);
    menus[Menu::SETTINGS_GAME] = std::make_unique<Menu_Settings_Game>(saveSettings);
    menus[Menu::SETTINGS_GENERAL] = std::make_unique<Menu_Settings_General>();
    menus[Menu::SETTINGS_AUDIO] = std::make_unique<Menu_Settings_Audio>(audio);

    auto saveCommands = std::bind(&Game_State::loadCommands, game, std::placeholders::_1);
    menus[Menu::SETTINGS_KEYMAPPER] = std::make_unique<Menu_Settings_Keymapper>(saveCommands);

    menus[Menu::NEW_GAME] = std::make_unique<Menu_New_Game>();
    menus[Menu::LOAD_GAME] = std::make_unique<Menu_Load_Game>();
    menus[Menu::SAVE_GAME] = std::make_unique<Menu_Save_Game>();

    menu = menus[Menu::MAIN].get();
    drawables.push_back(menu);
}

void Menu_State::update(float delta_time)
{
    const sf::Vector2i mpos = sf::Mouse::getPosition();
    menu->update(mpos);
}

void Menu_State::handleInput(const sf::Event& event)
{
    menu->handleInput(event);
}

void Menu_State::setMenuState(Menu::State new_menu)
{
    menu->exitState();
    menu->reset();
    menu = menus[new_menu].get();
    menu->enterState();
    drawables[0] = menu;
    if ((new_menu == Menu::SETTINGS && current_menu <= Menu::PAUSE)
     || (new_menu == Menu::LOAD_GAME || new_menu == Menu::SAVE_GAME)) {
        menu->setEscape(current_menu);
    }
    last_menu = current_menu;
    current_menu = new_menu;
}
