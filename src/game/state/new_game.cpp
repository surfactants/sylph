#include <game/state/new_game.hpp>

#include <engine/math/primordial.hpp>
#include <engine/math/prng.hpp>

#include <game/core/load_game.hpp>

#include <game/world/world.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    initializeCore();
    // read data into core
    // add asynchronous tasks
    addTask(std::bind(finalPrep, this));
}

New_Game::New_Game(std::filesystem::path load_path)
{
    initializeCore();
    addTask(std::bind(load, this, load_path));
    addTask(std::bind(finalPrep, this));
}

void New_Game::finalPrep()
{
    thread_done.test_and_set();
}

void New_Game::update(const float delta_time)
{
    if (Async_Loader::update()) {
        newToPlay();
    }
    // check renderer?
}

void New_Game::loadSettings(Game_Settings settings)
{
    this->settings = settings;
    // propagate...
}

void New_Game::createWorld()
{
    World world(data, core.get());
    thread_done.test_and_set();
}

void New_Game::load(std::filesystem::path load_path)
{
    Load_Game(core.get(), load_path);
    thread_done.test_and_set();
}

void New_Game::clickLeft()
{}

void New_Game::releaseLeft()
{}

void New_Game::clickRight()
{}

void New_Game::releaseRight()
{}

void New_Game::clickMiddle()
{}

void New_Game::releaseMiddle()
{}
