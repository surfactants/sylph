#include <game/state/game.hpp>

Game_Settings Game::settings;

std::function<void(Game::State)> Game::setGameState;

std::function<sf::Vector2f(sf::View)> Game::relativeMousePos;

std::unique_ptr<ECS_Core> Game::core { nullptr };

System_Manager* Game::systems { nullptr };

std::function<void(const Date&)> Game::updateDate;
std::function<void(const Resource&)> Game::updateResourcePanel;

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

void Game::clickLeft()
{
    switch (systems->context()) {
        case Context::GALACTIC:
            systems->tile_system.activate();
            break;
        case Context::SOLAR:
            systems->solar_system.activate();
            break;
    }
}

void Game::releaseLeft()
{ }

void Game::clickRight()
{
    switch (systems->context()) {
        case Context::GALACTIC:
            systems->tile_system.deactivate();
            break;
        case Context::SOLAR:
            systems->solar_system.deactivate();
            break;
    }
}

void Game::releaseRight()
{ }

void Game::clickMiddle()
{
    const sf::Vector2f mpos = relativeMousePos(*systems->context.current_view);
    systems->camera_controller.startDrag(mpos);
}

void Game::releaseMiddle()
{
    const sf::Vector2f mpos = relativeMousePos(*systems->context.current_view);
    systems->camera_controller.endDrag(mpos);
}

void Game::controlCamera(const sf::Vector2f& mpos, const float delta_time)
{
    sf::Vector2f v = systems->accelerator.update(delta_time);
    systems->camera_controller.update(v, mpos);
}

void Game::contextUpdate(const sf::Vector2f& mpos)
{
    switch (systems->context()) {
        case Context::GALACTIC:
            systems->tile_system.update(mpos);
            break;
        case Context::SOLAR:
            systems->solar_system.update(mpos);
    }
}
