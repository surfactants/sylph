#include <game/state/new_game.hpp>

#include <engine/math/primordial.hpp>
#include <engine/math/prng.hpp>

#include <game/core/load_game.hpp>

#include <game/world/world.hpp>
#include <game/world/civilization_generator.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    initializeCore();
    core->info.player_name = data.player_name;
    addTask(std::bind(createWorld, this));
    addTask(std::bind(createCivilizations, this));
    addTask(std::bind(finalPrep, this));
}

New_Game::New_Game(std::filesystem::path load_path)
{
    initializeCore();
    core->info.player_name = data.player_name;
    addTask(std::bind(load, this, load_path));
    addTask(std::bind(finalPrep, this));
}

void New_Game::finalPrep()
{
    core->systems.context.world_bounds = Collision_Rect(core->info.world_bounds);
    core->systems.context.set(Context::GALACTIC, NULL_ENTITY);

    // populate tile system based on player's home system
    const auto& civ_data = core->components.getComponent<Civilization_Data>(core->info.player);
    core->systems.tile_system.setTileVisible(civ_data.capital_system);

    const auto& hierarchy = core->components.getComponent<Hierarchy>(civ_data.capital_system);
    for (const auto& neighbor : hierarchy.neighbors) {
        core->systems.tile_system.setTileVisible(neighbor);
    }

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
