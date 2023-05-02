#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

Component_Manager Game::components;

System_Manager Game::systems;

Renderer Game::renderer;

Entity_Manager Game::entities;

void Game::reset()
{}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}
