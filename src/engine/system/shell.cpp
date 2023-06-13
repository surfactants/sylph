#include <engine/system/shell.hpp>

#include <engine/database/database_commands.hpp>
#include <engine/input/command.hpp>

#include <engine/system/game_state.hpp> // for assigning loadGame

#include <ui/menu/menu_load_game.hpp> // for assigning loadGame
#include <ui/menu/menu_settings_general.hpp> // for assigning resizeWindow

#include <game/state/game.hpp> // for assigning relativeMousePos
// abstract it through the state machine later - it will need assigning in multiple places anyway

#include <engine/resources/font_manager.hpp> // for fps

Shell::Shell()
    : window { sf::VideoMode::getDesktopMode(), "sylph x", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 2) }
{
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

    Game_State* game_state = dynamic_cast<Game_State*>(state.states[Main_State::GAME].get());
    Menu_Load_Game::loadGame = std::bind(&Game_State::loadGame, game_state, std::placeholders::_1);
    Menu_Settings_General::resizeWindow = std::bind(resizeWindow, this, std::placeholders::_1);

    fps_text.setFont(*Font_Manager::get(Font::MENU));
    fps_text.setCharacterSize(36);
    fps_text.setPosition(sf::Vector2f(1800.f, 8.f));

    System_Manager::relativeMousePos = [&](sf::View v) {
        return window.mapPixelToCoords(sf::Mouse::getPosition(), v);
    };

    resizeWindow(window.getSize());
}

void Shell::run()
{
    while (window.isOpen()) {
        float time = fps_clock.restart().asSeconds();
        fps_text.setString(std::to_string(static_cast<int>(1 / time)));
        update();
        draw();
    }
}

void Shell::setAntiAliasing()
{ }

void Shell::update()
{
    while (window.pollEvent(event)) {
        state.handleInput(event);
    }
    state.update(1.f);
    //audio.update();
}

void Shell::draw()
{
    window.clear();
    window.draw(state);
    //window.draw(fps_text);
    window.display();
}

void Shell::resizeWindow(sf::Vector2u w_size)
{
    window.setSize(w_size);
    state.windowResize(w_size);
}
