#include <game/world/system_generator.hpp>

#include <SFML/Graphics/CircleShape.hpp> // for orbital radius

#include <cmath> // pow

#include <engine/database/database_body.hpp>
#include <engine/util/prng.hpp>

#include <game/component/body_info.hpp>
#include <game/component/transform.hpp>

#include <engine/util/sfml_stream.hpp>

System_Generator::System_Generator(Component_Manager& components, Entity_Manager& entities)
    : components { components }
    , entities { entities }
{
    Database_Body db;
    std::vector<std::pair<Body_Info, Body_Info>> bodies;
    bodies = db.read();
    float s_chance = 0.f;
    for (const auto& body : bodies) {
        Body_Info min = body.first;
        Body_Info max = body.second;

        if (min.type == "star") {
            star_min[min.subtype] = min;
            star_max[max.subtype] = max;
            s_chance += min.chance;
            star_chance.push_back(std::make_pair(s_chance, min.subtype));
        }
        else {
            planet_min[min.subtype] = min;
            planet_max[max.subtype] = max;
        }
    }
}

void System_Generator::make(Entity system)
{
    Entity star = makeStar(system);
    makePlanets(system, star);
}

Entity System_Generator::makeStar(Entity system)
{
    // initialize entity
    Entity star = entities.create();
    Signature sig;

    sig.set(toInt(Component::BODY_INFO));
    sig.set(toInt(Component::HIERARCHY));
    sig.set(toInt(Component::TRANSFORM));
    sig.set(toInt(Component::RESOURCE));

    entities.define(star, sig);

    std::string subtype = randomStar();
    Body_Info min = star_min[subtype];
    Body_Info max = star_max[subtype];

    Body_Info s_info;
    s_info.name = alphanumericName();
    s_info.description = min.description;
    s_info.type = "star";
    s_info.subtype = subtype;
    s_info.radius = prng::number(min.radius, max.radius);
    s_info.temperature = prng::number(min.temperature, max.temperature);
    s_info.light = prng::number(min.light, max.light);
    s_info.color.r = prng::number(min.color.r, max.color.r);
    s_info.color.g = prng::number(min.color.g, max.color.g);
    s_info.color.b = prng::number(min.color.b, max.color.b);
    components.addComponent(star, s_info);

    Resource resource;
    components.addComponent(star, resource);

    Hierarchy s_hierarchy;
    s_hierarchy.parent = { system };
    components.addComponent(star, s_hierarchy);

    Transform transform;
    components.addComponent(star, transform);

    s_info.type = "system";
    s_info.description = "an undefined solar system";
    components.addComponent(system, s_info);
    components.addComponent(system, resource);

    return star;
}

void System_Generator::makePlanets(Entity system, Entity star)
{
    size_t count = prng::number(1, 17);

    Hierarchy system_hierarchy;
    system_hierarchy.child = { star };

    float orbital_radius = components.getComponent<Body_Info>(star).radius;

    constexpr static float radius_diff_min { 512.f };
    constexpr static float radius_diff_max { 2048.f };

    for (size_t i = 0; i < count; i++) {
        orbital_radius += prng::number(radius_diff_min, radius_diff_max);

        Entity body = entities.create();

        Signature sig;

        sig.set(toInt(Component::BODY_INFO));
        sig.set(toInt(Component::HIERARCHY));
        sig.set(toInt(Component::TRANSFORM));
        sig.set(toInt(Component::RESOURCE));

        entities.define(body, sig);

        std::string subtype = randomPlanet(star, orbital_radius);
        Body_Info min = planet_min[subtype];
        Body_Info max = planet_max[subtype];

        Body_Info b_info;
        b_info.name = alphanumericName();
        b_info.description = min.description;
        b_info.type = "planet";
        b_info.subtype = subtype;
        b_info.radius = prng::number(min.radius, max.radius);
        b_info.orbit = orbital_radius;
        b_info.temperature = prng::number(min.temperature, max.temperature);
        b_info.light = prng::number(min.light, max.light);
        b_info.color.r = prng::number(min.color.r, max.color.r);
        b_info.color.g = prng::number(min.color.g, max.color.g);
        b_info.color.b = prng::number(min.color.b, max.color.b);
        components.addComponent(body, b_info);

        Hierarchy b_hierarchy;
        b_hierarchy.parent = { system };
        components.addComponent(body, b_hierarchy);

        unsigned int point_count = std::pow(orbital_radius, .5) + 1;
        sf::CircleShape orbit(orbital_radius, point_count);

        Transform transform;
        unsigned int point = prng::number(orbit.getPointCount());
        transform.position = orbit.getPoint(point) - sf::Vector2f(orbital_radius, orbital_radius);
        components.addComponent(body, transform);

        orbital_radius += b_info.radius; // "clearing the neighborhood";

        system_hierarchy.child.push_back(body);

        makeResource(body);
    }

    Collision_Rect system_bounds;
    orbital_radius += 2000.f;
    system_bounds.setPosition(sf::Vector2f(-orbital_radius, -orbital_radius));
    system_bounds.setSize(sf::Vector2f(orbital_radius * 2.f, orbital_radius * 2.f));

    components.addComponent(system, system_bounds);

    components.addComponent(system, system_hierarchy);
}

void System_Generator::makeResource(Entity planet)
{
    Resource resource;

    auto& info = components.getComponent<Body_Info>(planet);
    std::string type = info.subtype;
    float size = info.radius;

    if (type == "telluric") {
        resource.set(Resource::METALS, prng::number(0.1f, 2.5f));
        resource.set(Resource::RARE_METALS, prng::number(0.f, 0.8f));
        resource.set(Resource::SILICATES, prng::number(1.f, 10.f));
        resource.set(Resource::HYDROCARBONS, prng::number(0.f, 0.8f));
        resource.set(Resource::WATER, prng::number(0.f, 5.f));
    }
    else if (type == "frozen") {
        resource.set(Resource::WATER, prng::number(1.f, 5.f));
        resource.set(Resource::SILICATES, prng::number(0.f, 1.f));
        resource.set(Resource::METALS, prng::number(0.f, 1.f));
    }
    else if (type == "gas giant") {
        resource.set(Resource::HYDROGEN, prng::number(1.f, 5.f));
        resource.set(Resource::HELIUM3, prng::number(0.25f, 2.5f));
    }
    else if (type == "ice giant") {
        resource.set(Resource::WATER, prng::number(0.5f, 1.5f));
        resource.set(Resource::HYDROCARBONS, prng::number(1.f, 4.f));
        resource.set(Resource::AMMONIA, prng::number(1.f, 4.f));
    }

    components.addComponent(planet, resource);
}

std::string System_Generator::randomStar()
{
    float roll = prng::number(0.f, 100.f);
    size_t n = star_chance.size();
    for (size_t i = 1; i < n; i++) {
        if (roll < star_chance[i].first
         && roll > star_chance[i - 1].first) {
            return star_chance[i].second;
        }
    }
    return star_chance[0].second;
}

std::string System_Generator::randomPlanet(Entity star, float orbital_radius)
{
    std::string subtype;

    Body_Info star_info = components.getComponent<Body_Info>(star);

    // calculate temperature from star here
    // solar radiation received follows an inverse square law
    // however, the abstractions inherent in this necessitate a different approach

    //float t = star_info.temperature / (orbital_radius / (star_info.radius / 2.f));
    float t = star_info.temperature / (orbital_radius / star_info.radius);
    //t *= 1 / std::pow(orbital_radius / star_info.radius, 2);

    // later, factor in atmosphere

    std::vector<std::string> allowed_planets;

    for (const auto& m : planet_min) {
        if (t > m.second.temperature && t < planet_max[m.second.subtype].temperature) {
            allowed_planets.push_back(m.second.subtype);
        }
    }
    if (allowed_planets.size() == 0) {
        std::cout << "FAILED TO FIND ANY PLANETS!\n\n";

        return "telluric";
    }

    return allowed_planets[prng::number(allowed_planets.size())];
}

std::string System_Generator::alphanumericName()
{
    std::string name {};
    int chars = prng::number(1, 3);
    for (int i = 0; i < chars; i++) {
        name += prng::number('A', 'Z');
    }
    name += '-' + std::to_string(prng::number(0, 9999));
    return name;
}
