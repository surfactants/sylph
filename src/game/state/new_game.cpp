#include <game/state/new_game.hpp>

#include <engine/math/primordial.hpp>
#include <engine/util/prng.hpp>

#include <game/world/world.hpp>
#include <game/world/empire_generator.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    tasks.push_back(std::bind(createWorld, this));
    tasks.push_back(std::bind(createEmpires, this));

    thread_done.test_and_set();
}

void New_Game::update(float delta_time)
{
    if (thread_done.test()) {
        thread_done.clear();
        if (task_index == tasks.size()) {
            if (thread.joinable()) {
                thread.join();
            }
            // initiate transition to play
            task_index = 0;
            newToPlay();
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
    World world(data, components, entities, systems);
    systems.context.world_bounds = world.getFrame();
    systems.context.set(Context::GALACTIC, MAX_ENTITIES);
    thread_done.test_and_set();
}

void New_Game::createEmpires()
{
    Empire_Generator empire_generator(data, components, entities, systems);
    thread_done.test_and_set();
}

void New_Game::createPlayer()
{
    Entity player = entities.create();

    Signature s;
    s.set(toInt(Component::TRANSFORM));
    s.set(toInt(Component::COLLISION_RECT));
    entities.define(player, s);
    thread_done.test_and_set();
}

void New_Game::clickLeft()
{ }

void New_Game::releaseLeft()
{ }

void New_Game::clickRight()
{ }

void New_Game::releaseRight()
{ }

void New_Game::clickMiddle()
{ }

void New_Game::releaseMiddle()
{ }
