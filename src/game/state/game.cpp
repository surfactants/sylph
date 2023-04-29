#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

Component_Manager Game::components;

Renderer Game::renderer;

Game::Game()
{
}

Game::Game(const Game& g)
    : entities { g.getEntities() }
{
}

Game::~Game()
{
    renderer.clear();
}

void Game::addEntity(Entity e, std::vector<Component*> c)
{
    components.registerEntity(e, c);
}

void Game::reset()
{
    components.clear();
    entities.reset();
}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}

Renderer* Game::getRenderer()
{
    return &renderer;
}

const Entity_Manager& Game::getEntities() const
{
    return entities;
}
