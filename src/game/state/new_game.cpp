#include <game/state/new_game.hpp>

#include <iostream>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    world = std::make_unique<World>();
    tasks.push_back(std::bind(createWorld, this));
    tasks.push_back(std::bind(createPlayer, this));
    thread_done.test_and_set();
}

void New_Game::update(float delta_time, const sf::Vector2f& mpos)
{
    if (thread_done.test()) {
        thread_done.clear();
        if (task_index == tasks.size()) {
            if (thread.joinable()) {
                thread.join();
            }
            // initiate transition to play
            newToPlay();
            task_index = 0;
            return;
        }
        else {
            // launch next thread
            if (thread.joinable()) {
                thread.join();
            }
            thread = std::thread(tasks[task_index]);
            task_index++;
        }
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
    world->load(data);
    thread_done.test_and_set();
}

void New_Game::createPlayer()
{
    Entity player = entities.create();
    Signature s;
    s.flip(Component::toInt(Component::HEALTH));
    s.flip(Component::toInt(Component::ANIMATED_SPRITE));
    entities.define(player, s);
    thread_done.test_and_set();
}
