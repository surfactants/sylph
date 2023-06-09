#include <game/state/new_game.hpp>

#include <engine/math/primordial.hpp>
#include <engine/util/prng.hpp>

#include <game/core/load_game.hpp>

#include <game/world/world.hpp>
#include <game/world/civilization_generator.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    tasks.clear();

    core = std::make_unique<ECS_Core>();
    core->info.player_name = data.player_name;
    tasks.push_back(std::bind(createWorld, this));
    tasks.push_back(std::bind(createCivilizations, this));

    thread_done.test_and_set();
}

New_Game::New_Game(std::filesystem::path load_path)
{
    tasks.clear();

    core = std::make_unique<ECS_Core>();
    core->info.player_name = data.player_name;
    tasks.push_back(std::bind(load, this, load_path));

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
            core->systems.context.world_bounds = Collision_Rect(core->info.world_bounds);
            core->systems.context.set(Context::GALACTIC, MAX_ENTITIES);
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
    World world(data, core.get());
    core->info.world_bounds = world.getFrame();
    thread_done.test_and_set();
}

void New_Game::createCivilizations()
{
    Civilization_Generator civilization_generator(data, Game::core.get());
    thread_done.test_and_set();
}

void New_Game::load(std::filesystem::path load_path)
{
    Load_Game(core.get(), load_path);
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
