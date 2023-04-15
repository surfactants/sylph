#include <game/state/game.hpp>

Game_Settings Game::settings;

Game::Game()
{}

void Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate
}
