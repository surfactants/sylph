#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

std::unique_ptr<ECS_Core> Game::core { nullptr };

System_Manager* Game::systems { nullptr };

void Game::initializeCore()
{
    core = std::make_unique<ECS_Core>();
    systems = &(core->systems);
}

void Game::reset()
{
    core = nullptr;
    systems = nullptr;
}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}
