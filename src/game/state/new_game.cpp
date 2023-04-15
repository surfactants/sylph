#include <game/state/new_game.hpp>

#include <engine/util/vector2_stream.hpp>

#include <SFML/System/Clock.hpp>

std::function<void()> New_Game::newToPlay;

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

    tasks.push_back(std::bind(createWorld, this));
}

void New_Game::update(float delta_time)
{
    if (thread_done.test()) {
        thread_done.clear();
        if (task_index == tasks.size()) {
            // initiate transition to play
            newToPlay();
            task_index = 0;
            return;
        }
        else {
            // launch next thread
            thread = std::thread(tasks[task_index]);
            task_index++;
        }
        // proceed to next thread OR initiate transition to play
    }
    // render screen
}

void New_Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate...
}

void New_Game::createWorld()
{
    float threshold { 5.f };
    sf::Clock timer;
    while (timer.getElapsedTime().asSeconds() < threshold);
    thread_done.test_and_set();
}
