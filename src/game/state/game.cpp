#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

std::unique_ptr<ECS_Core> Game::core { nullptr };

void Game::reset()
{}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}
