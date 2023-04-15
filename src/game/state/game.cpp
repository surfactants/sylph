#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

Game::Game()
{}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}

const World& Game::getWorld() const
{
    return world;
}

const Entity_Manager& Game::getEntities() const
{
    return entities;
}
