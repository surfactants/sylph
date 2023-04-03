#include <system/main_state/game_state.hpp>

#include <game/game_play.hpp>

Game_State::Game_State()
{
    states[Game::PLAY] = std::make_unique<Game_Play>();
}

void Game_State::update(float delta_time)
{}

void Game_State::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            openPauseMenu();
        }
    }
}

void Game_State::setGameState(Game::State new_game)
{
    game = states[new_game].get();
}
