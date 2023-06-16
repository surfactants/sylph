#include <engine/shell/menu_state.hpp>

#include <engine/database/database_commands.hpp>

#include <ui/menu/states.hpp>

Menu_State::Menu_State(Audio& audio, Game_State* game)
{
    UI::setUIState = std::bind(setState, this, std::placeholders::_1);

    UI::clearGame = std::bind(&Game_State::clear, game);

    menus[UI::TITLE] = std::make_unique<Menu_Title>();
    current.state = UI::TITLE;
    current.ptr = menus[UI::TITLE].get();
    last = current;

    menus[UI::PAUSE] = std::make_unique<Menu_Pause>();
    menus[UI::SETTINGS] = std::make_unique<Menu_Settings>();

    auto saveSettings = std::bind(&Game_State::loadSettings, game, std::placeholders::_1);
    menus[UI::SETTINGS_GAME] = std::make_unique<Menu_Settings_Game>(saveSettings);
    menus[UI::SETTINGS_GENERAL] = std::make_unique<Menu_Settings_General>();
    menus[UI::SETTINGS_AUDIO] = std::make_unique<Menu_Settings_Audio>(audio);

    auto saveCommands = std::bind(&Game_State::loadCommands, game, std::placeholders::_1);
    menus[UI::SETTINGS_KEYMAPPER] = std::make_unique<Menu_Settings_Keymapper>(saveCommands);

    auto start_game = std::bind(&Game_State::newGame, game, std::placeholders::_1);
    menus[UI::NEW_GAME] = std::make_unique<Menu_New_Game>(start_game);
    menus[UI::LOAD_GAME] = std::make_unique<Menu_Load_Game>();
    menus[UI::SAVE_GAME] = std::make_unique<Menu_Save_Game>();

    drawables.push_back(current.ptr);
}

void Menu_State::update(const float delta_time)
{
    const sf::Vector2i mpos = sf::Mouse::getPosition();
    current.ptr->update(mpos);
}

void Menu_State::handleInput(const sf::Event& event)
{
    current.ptr->handleInput(event);
}

void Menu_State::windowResize(const sf::Vector2u& w_size)
{
    Menu::setView(w_size);
    for (auto& m : menus) {
        m.second->windowResize(w_size);
    }
}

void Menu_State::setState(UI::State new_menu)
{
    last = current;
    last.ptr->exitState();
    last.ptr->reset();
    current.ptr = menus[new_menu].get();
    current.state = new_menu;
    current.ptr->enterState();
    drawables[0] = current.ptr;

    if ((new_menu == UI::SETTINGS && last.state <= UI::PAUSE)
     || new_menu == UI::LOAD_GAME) {
        current.ptr->setEscape(last.state);
    }
}
