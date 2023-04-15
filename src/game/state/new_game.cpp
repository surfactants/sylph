#include <game/state/new_game.hpp>

#include <engine/util/vector2_stream.hpp>

New_Game::New_Game(New_Game_Data data)
{
    Entity player = entities.create();
    Signature s;
    s.flip(Component::toInt(Component::ANIMATED_SPRITE));
    entities.define(player, s);

    std::cout << "______________________________\n";
    std::cout << "LOADING NEW GAME!\n";
    std::cout << "player name: " << data.player_name << '\n';
    std::cout << "player color: " << data.player_color << '\n';
}

void New_Game::update(float delta_time)
{}

void New_Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate...
}
