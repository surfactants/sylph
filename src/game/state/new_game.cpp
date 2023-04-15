#include <game/state/new_game.hpp>

New_Game::New_Game()
{
    Entity player = entities.create();
    Signature s;
    s.flip(Component::toInt(Component::ANIMATED_SPRITE));
    entities.define(player, s);
}

void New_Game::update(float delta_time)
{
}

void New_Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate...
}
