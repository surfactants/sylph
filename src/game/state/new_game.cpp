#include <game/state/new_game.hpp>

#include <game/world/world.hpp>

#include <engine/util/sfml_stream.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    // find another place to assign these
    components.registerComponent<Collision_Rect>();
    components.registerComponent<Transform>();
    components.registerComponent<Polygon_Tile>();
    components.registerComponent<Tile>();

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
    World world(data);
    //std::vector<Tile> tiles = world.tiles();
    std::vector<std::pair<Transform, Polygon_Tile>> tiles = world.polygonTiles();
    // get world bounds with World::getFrame() - returns Collision_Rect component
    for (auto& t : tiles) {
        Signature s;

        s.set(toInt(Component::POLYGON_TILE));
        s.set(toInt(Component::TRANSFORM));

        Entity e = entities.create();
        entities.define(e, s);

        components.addComponent(e, t.first);
        components.addComponent(e, t.second);

        systems.tile_system.addTile(e);

        // read components into component manager
        // get pointers to those components and pass to the pertinent systems
    }
    systems.camera_controller.bounds = world.getFrame();
    float max_zoom = world.getFrame().size.y / 1080.f; // window size, height....
    std::cout << "\n\ncalculated max zoom at " << max_zoom << " from " << world.getFrame().size << '\n';
    max_zoom = static_cast<int>(max_zoom) - 1; // ensures the view will never be too big for the bounds
    systems.camera_controller.max_zoom = max_zoom;
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
