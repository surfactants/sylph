#include <game/state/game_simulate.hpp>

#include <iostream>

void Game_Simulate::update(const float delta_time)
{
    const sf::Vector2f mpos = relativeMousePos(*(systems->context.current_view));
    controlCamera(mpos, delta_time);
    contextUpdate(mpos);

    if (step_timer.getElapsedTime().asSeconds() >= step_length) {
        step();
        step_timer.restart();
    }
}

void Game_Simulate::step()
{
    core->info.date.month++;

    bool ending { false };
    if (core->info.date.month > 12) {
        core->info.date.year++;
        core->info.date.month = 1;
        ending = true;
    }
    // TODO update player empire resources with core->info.player
    updateDate(core->info.date);

    Resource& resource = core->components.getComponent<Resource>(core->info.player);
    for (auto& row : resource.values) {
        row.second += 1.f;
    }
    updateResourcePanel(resource);

    if (ending) {
        setGameState(Game::PLAYER_TURN);
    }
}
