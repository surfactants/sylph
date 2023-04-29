#include <game/state/new_game.hpp>

#include <iostream>

#include <game/world/world.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
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
    World world(data);
    std::vector<Signature> signatures;
    //std::vector<Tile> tiles = world.tiles();
    std::vector<std::pair<Transform, Polygon_Tile>> tiles = world.polygonTiles();
    // get world bounds with World::getFrame() - returns Collision_Rect component
    for (auto& t : tiles) {
        Signature s;

        s.set(toInt(Component::COLLISION_RECT));
        s.set(toInt(Component::POLYGON_TILE));
        s.set(toInt(Component::TRANSFORM));

        Entity e = entities.create();
        entities.define(e, signatures.back());

        // read components into component manager
        // get pointers to those components and pass to the pertinent systems
    }
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
