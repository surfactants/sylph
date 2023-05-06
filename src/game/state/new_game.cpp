#include <game/state/new_game.hpp>

#include <engine/math/primordial.hpp>
#include <engine/util/prng.hpp>

#include <game/world/world.hpp>

std::function<void()> New_Game::newToPlay;

New_Game::New_Game(New_Game_Data data)
    : data { data }
{
    tasks.push_back(std::bind(createWorld, this));
    tasks.push_back(std::bind(createPlayer, this));

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
    World world(data);
    //std::vector<Tile> tiles = world.tiles();
    std::vector<std::pair<Transform, Polygon_Tile>> tiles = world.polygonTiles();
    // get world bounds with World::getFrame() - returns Collision_Rect component
    for (auto& t : tiles) {
        Signature s;

        s.set(toInt(Component::ENTITY_INFO));
        s.set(toInt(Component::COLOR));
        s.set(toInt(Component::POLYGON_TILE));
        s.set(toInt(Component::TRANSFORM));
        s.set(toInt(Component::HIERARCHY));
        s.set(toInt(Component::COLLISION_RECT));

        Entity_Info info;
        info.name = "system-" + std::to_string(prng::number(1, 999));
        info.description = "an undefined solar system";

        Entity e = entities.create();
        entities.define(e, s);

        components.addComponent(e, t.first);
        components.addComponent(e, t.second);
        components.addComponent(e, info);

        generateSystem(e);

        systems.tile_system.addTile(e);

        // read components into component manager
        // get pointers to those components and pass to the pertinent systems
    }
    systems.context.world_bounds = world.getFrame();
    systems.context.set(Context::GALACTIC, MAX_ENTITIES);
    thread_done.test_and_set();
}

void New_Game::generateSystem(Entity system)
{
    int r = prng::number(145, 245);
    int g = prng::number(125, 225);
    int b = prng::number(145, 245);
    Color color = Color(r, g, b);

    Transform transform; // for now stars are always (0, 0)

    Entity_Info info;
    info.name = "star " + std::to_string(prng::number(0, 999));
    info.description = "giant ball of fusing gas";

    Hierarchy h;
    h.parent = { system };

    Body_Info b_info;
    b_info.radius = prng::number(48.f, 112.f);

    Signature s;

    s.set(toInt(Component::ENTITY_INFO));
    s.set(toInt(Component::TRANSFORM));
    s.set(toInt(Component::COLOR));
    s.set(toInt(Component::HIERARCHY));
    s.set(toInt(Component::BODY_INFO));

    Entity star = entities.create();
    entities.define(star, s);
    components.addComponent(star, info);
    components.addComponent(star, transform);
    components.addComponent(star, color);
    components.addComponent(star, h);
    components.addComponent(star, b_info);

    components.addComponent(system, color);

    Hierarchy system_h;
    system_h.child.push_back(star);
    //children.push_back(star);

    // to place planets, define a circleshape with an increasing radius around the star
    // place the planet at a random point
    // add moons with the same strategy
    // figure out something special for asteroid belts
    float radius = 128.f;

    unsigned int n = prng::number(5, 15);
    for (unsigned int i = 0; i < n; i++) {
        radius += prng::number(512.f, 1024.f);
        unsigned int point_count = roundFloat(radius / 2.f); // find a better way to calculate this, with a ceiling
        sf::CircleShape orbit(radius, point_count);
        //orbit.setOrigin(sf::Vector2f(radius, radius));
        orbit.setPosition(sf::Vector2f(-radius * 10.f, -radius * 10.f));
        s.reset();
        Entity body = entities.create();
        system_h.child.push_back(body);
        s.set(toInt(Component::ENTITY_INFO));
        s.set(toInt(Component::TRANSFORM));
        s.set(toInt(Component::COLOR));
        s.set(toInt(Component::HIERARCHY));
        entities.define(body, s);

        info.name = "planet " + std::to_string(prng::number(0, 99999));
        info.description = "a ball* of rock, or maybe ice. it might even be a gas giant!\n*or some other shape";
        components.addComponent(body, info);

        sf::Vector2f pos;
        pos = orbit.getPoint(prng::number(orbit.getPointCount())) - sf::Vector2f(radius, radius);
        transform.position = pos;
        components.addComponent(body, transform);

        int r = prng::number(10, 245);
        int g = prng::number(10, 245);
        int b = prng::number(10, 245);
        color = Color(r, g, b);
        components.addComponent(body, color);
        components.addComponent(body, h);

        b_info.radius = prng::number(18.f, 44.f);
        b_info.orbit = radius;
        components.addComponent(body, b_info);
    }

    radius += 512.f;

    Collision_Rect bounds;
    bounds.setPosition(sf::Vector2f(-radius, -radius));
    bounds.setSize(sf::Vector2f(radius * 2.f, radius * 2.f));

    components.addComponent(system, bounds);
    components.addComponent(system, system_h);
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
