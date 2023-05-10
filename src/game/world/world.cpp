#include <game/world/world.hpp>

#include <cassert>

#include <engine/math/collide.hpp>
#include <engine/util/prng.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

World::World(New_Game_Data data
    , Component_Manager& components
    , Entity_Manager& entities
    , System_Manager& systems)
    : data { data }
    , components { components }
    , entities { entities }
    , systems { systems }
{
    generateSystems();
}

Collision_Rect World::getFrame()
{
    return frame;
}

void World::generateSystems()
{
    size_t point_upper_bound;
    size_t point_lower_bound;

    float size_factor;

    min = sf::Vector2f(0.f, 0.f);

    switch (data.size) {
        case New_Game_Data::SMALL:
            point_lower_bound = 150;
            point_upper_bound = 250;
            size_factor = 4.f;
            break;
        case New_Game_Data::MEDIUM:
            point_lower_bound = 350;
            point_upper_bound = 450;
            size_factor = 8.f;
            break;
        case New_Game_Data::LARGE: // * 8
            point_lower_bound = 550;
            point_upper_bound = 650;
            size_factor = 12.f;
            break;
        case New_Game_Data::VERY_LARGE: // * 8
            point_lower_bound = 750;
            point_upper_bound = 850;
            size_factor = 16.f;
            break;
    }

    max = sf::Vector2f(1920.f, 1080.f);
    max *= size_factor;

    size_t point_count = prng::number(point_lower_bound, point_upper_bound);
    sf::Vector2<double> world_min(min);
    sf::Vector2<double> world_max(max);

    Voronoi::Diagram d(point_count, world_min, world_max);
    std::vector<sf::ConvexShape> cells = d.get();
    std::vector<sf::Vector2f> sites = d.sites();

    size_t n = cells.size();

    for (size_t i = 0; i < n; i++) {
        // make systems
        Transform transform;
        transform.position = sites[i];
        Polygon_Tile tile;
        size_t p = cells[i].getPointCount();
        for (size_t j = 0; j < p; j++) {
            tile.vertices.push_back(cells[i].getPoint(j));
        }

        Signature s;

        //s.set(toInt(Component::ENTITY_INFO));
        //s.set(toInt(Component::COLOR));
        s.set(toInt(Component::BODY_INFO));
        s.set(toInt(Component::POLYGON_TILE));
        s.set(toInt(Component::TRANSFORM));
        s.set(toInt(Component::HIERARCHY));
        s.set(toInt(Component::COLLISION_RECT));

        Entity system = entities.create();
        entities.define(system, s);

        components.addComponent(system, tile);
        components.addComponent(system, transform);
        //components.addComponent(system, e_info);

        system_generator.make(system);
        //makeSystem(system);

        systems.tile_system.addTile(system);
    }

    min -= sf::Vector2f(512.f, 512.f);
    max += sf::Vector2f(512.f, 512.f);

    frame.setPosition(sf::Vector2f(min));
    frame.setSize(sf::Vector2f(max - min));
}
/*
void World::makeSystem(Entity system)
{
    // operate on system_generator here

    // stars (just one for now)

    Entity star = makeStar(system);

    // planets/moons/asteroids. also adds system hierarchy and bounds
    makePlanets(system, star);
}

Entity World::makeStar(Entity system)
{
    // set up a separate class for all this, especially wrt lookups for things like color

    // initialize entity
    Entity star = entities.create();
    Signature sig;

    sig.set(toInt(Component::HIERARCHY));
    sig.set(toInt(Component::TRANSFORM));
    sig.set(toInt(Component::BODY_INFO));
    sig.set(toInt(Component::COLOR));
    sig.set(toInt(Component::ENTITY_INFO));

    entities.define(star, sig);

// define components:
    // hierarchy
    Hierarchy hierarchy;
    hierarchy.parent = { system };
    components.addComponent(star, hierarchy);

    // empty transform suffices in unary systems
    Transform transform;
    transform.position = sf::Vector2f(0.f, 0.f);
    components.addComponent(star, transform);

    // body info needs to be determined before color and entity info
    Body_Info b_info;
    b_info.type = "star";

    const std::vector<std::string> classes = { // Morgan-Keenan
        "O", // deep blue
        "B", // blue
        "A", // blue white
        "F", // white
        "G", // yellow
        "K", // light orange
        "M"  // orange red
    };

    // most stars are m class. don't worry about that yet.
    size_t star_class = prng::number(classes.size());
    b_info.subtype = classes[star_class];
    b_info.radius = prng::number(192.f, 312.f);
    components.addComponent(star, b_info);

    // color
    int rmin = 0;
    int rmax = 255;
    int gmin = 0;
    int gmax = 255;
    int bmin = 0;
    int bmax = 255;

    switch (star_class) {
        case 0: // O-class, deep blue
            rmin = 25;
            rmax = 90;
            bmin = 245;
            bmax = 255;
            gmin = 25;
            gmax = 90;
            break;
        case 1: // B-class star
            rmin = 45;
            rmax = 125;
            bmin = 245;
            bmax = 255;
            gmin = 45;
            gmax = 125;
            break;
        case 2: // A-class star
            rmin = 75;
            rmax = 185;
            bmin = 245;
            bmax = 255;
            gmin = 75;
            gmax = 185;
            break;
        case 3: // F-class
            rmin = 215;
            rmax = 255;
            bmin = 215;
            bmax = 255;
            gmin = 215;
            gmax = 255;
            break;
        case 4: // G-class
            rmin = 245;
            rmax = 255;
            bmin = 75;
            bmax = 185;
            gmin = 75;
            gmax = 185;
            break;
        case 5: // K-class
            rmin = 245;
            rmax = 255;
            bmin = 45;
            bmax = 125;
            gmin = 45;
            gmax = 125;
            break;
        case 6: // M-class
            rmin = 245;
            rmax = 255;
            bmin = 25;
            bmax = 90;
            gmin = 25;
            gmax = 90;
            break;
        default:
            break;
    }

    int rs = prng::number(rmin, rmax);
    int gs = prng::number(gmin, gmax);
    int bs = prng::number(bmin, bmax);

    Color color(rs, gs, bs);
    components.addComponent(star, color);
    components.addComponent(system, color);

    // entity info
    Entity_Info e_info;
    int chars = prng::number(1, 3);
    for (int i = 0; i < chars; i++) {
        e_info.name += prng::number('A', 'Z');
    }
    e_info.name += '-' + std::to_string(prng::number(0, 999));
    e_info.description = "yeowch! hot!";
    components.addComponent(star, e_info);

    components.addComponent(system, b_info);

    return star;
}

void World::makePlanets(Entity system, Entity star)
{
    Hierarchy system_hierarchy;
    system_hierarchy.child = { star };

    float orbital_radius = 0.f;
    constexpr float orbital_diff_min { 512.f };
    constexpr float orbital_diff_max { orbital_diff_min * 3.f };

    Hierarchy body_hierarchy;
    body_hierarchy.parent = { system };

    size_t n = prng::number(5, 15);

    for (size_t i = 0; i < n; i++) {
        orbital_radius += prng::number(orbital_diff_min, orbital_diff_max);
        unsigned int point_count = roundFloat(orbital_radius / 2.f);
        sf::CircleShape orbit(orbital_radius, point_count);

        Entity body = entities.create();
        system_hierarchy.child.push_back(body);
        Signature sig;
        sig.set(toInt(Component::ENTITY_INFO));
        sig.set(toInt(Component::BODY_INFO));
        sig.set(toInt(Component::TRANSFORM));
        sig.set(toInt(Component::COLOR));
        sig.set(toInt(Component::HIERARCHY));
        entities.define(body, sig);

        Entity_Info e_info;
        Body_Info b_info;
        std::vector<std::pair<std::string, std::string>> types = {
            { "chthonian", "a former gas giant, stripped of its atmosphere" },
            { "hycean", "covered in a global ocean" },
            { "telluric", "a silicaceous world" },
            { "frozen", "entirely covered by a thick sheet of ice" },
            { "molten", "tidal forces have rendered this planet into something resembling soup" },
            { "demon", "temperatures hot enough to heat metal, and a crushing, toxic atmosphere" },
            { "gas giant", "while the outer layers are gaseous, pressure maintains a deep, roiling sea of supercritical hydrogen and helium" },
            { "ice giant", "like a gas giant, but comprised of frozen volatiles" },
            { "protoplanet", "it's a baby planet!" },
            { "brown dwarf", "a star that didn't quite make it" }
        };

        size_t planet_class = prng::number(types.size());
        b_info.type = types[planet_class].first;
        e_info.description = types[planet_class].second;
        std::vector<std::string> subtypes;
        float radmin { 0.f };
        float radmax { 0.f };
        if (b_info.type == "brown dwarf") {
            radmin = 156.f;
            radmax = 188.f;
        }
        else if (b_info.type == "gas giant" || b_info.type == "ice giant") {
            radmin = 130.f;
            radmax = 184.f;
        }
        else {
            radmin = 64.f;
            radmax = 126.f;
        }
        b_info.subtype = "m";
        b_info.radius = prng::number(radmin, radmax);
        b_info.orbit = orbital_radius;
        components.addComponent(body, b_info);

        Transform transform;
        unsigned int point = prng::number(orbit.getPointCount());
        transform.position = orbit.getPoint(point) - sf::Vector2f(orbital_radius, orbital_radius);
        components.addComponent(body, transform);

        int r = prng::number(10, 245);
        int g = prng::number(10, 245);
        int b = prng::number(10, 245);
        Color color(r, g, b);
        components.addComponent(body, color);

        int chars = prng::number(1, 3);
        for (int i = 0; i < chars; i++) {
            e_info.name += prng::number('A', 'Z');
        }
        e_info.name += '-' + std::to_string(prng::number(0, 999));
        components.addComponent(body, e_info);

        components.addComponent(body, body_hierarchy);
    }


    orbital_radius += 512.f;

    Collision_Rect system_bounds;
    system_bounds.setPosition(sf::Vector2f(-orbital_radius, -orbital_radius));
    system_bounds.setSize(sf::Vector2f(orbital_radius * 2.f, orbital_radius * 2.f));

    components.addComponent(system, system_bounds);


    components.addComponent(system, system_hierarchy);

}
*/
