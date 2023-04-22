#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

std::unique_ptr<World> Game::world { nullptr };

Game::Game()
{}

void Game::deleteWorld()
{
    world.reset();
}

Game::Game(const Game& g)
    : entities { g.getEntities() }
{}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}

World* Game::getWorld()
{
    return world.get();
}

const Entity_Manager& Game::getEntities() const
{
    return entities;
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{}
