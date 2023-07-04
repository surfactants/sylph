#include <game/world/system_generator.hpp>

#include <SFML/Graphics/CircleShape.hpp> // for orbital radius

#include <cmath> // pow

#include <engine/database/database_body.hpp>
#include <engine/math/prng.hpp>

#include <engine/util/sfml_stream.hpp>

System_Generator::System_Generator(ECS_Core* core)
    : core { core }
{
    Database_Body db;
    std::vector<std::pair<Body_Info, Body_Info>> bodies;
    // these are complex types, use move
    bodies = std::move(db.bodies);
    body_descriptions = std::move(db.descriptions);
    resource_chances = std::move(db.resource_chances);
    resource_ranges = std::move(db.resource_ranges);
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

void System_Generator::make(Entity system, Hierarchy system_hierarchy)
{
    Entity star = makeStar(system);
    makePlanets(system, star, system_hierarchy);
}

Entity System_Generator::makeStar(Entity system)
{
    // initialize entity
    Entity star = core->entities.create();
    Signature sig;

    sig.set(toInt(Component::BODY_INFO));
    sig.set(toInt(Component::HIERARCHY));
    sig.set(toInt(Component::TRANSFORM));
    sig.set(toInt(Component::RESOURCE));
    sig.set(toInt(Component::ENTITY_DATA));

    core->entities.define(star, sig);

    std::string subtype = randomStar();
    Body_Info min = star_min[subtype];
    Body_Info max = star_max[subtype];

    Entity_Data e_data;
    e_data.name = alphanumericName();
    e_data.description = body_descriptions[subtype];
    core->components.addComponent(star, e_data);


    Body_Info s_info;
    s_info.type = "star";
    s_info.subtype = subtype;
    s_info.radius = prng::number(min.radius, max.radius);
    s_info.temperature = prng::number(min.temperature, max.temperature);
    s_info.light = prng::number(min.light, max.light);
    s_info.color.r = prng::number(min.color.r, max.color.r);
    s_info.color.g = prng::number(min.color.g, max.color.g);
    s_info.color.b = prng::number(min.color.b, max.color.b);
    core->components.addComponent(star, s_info);

    Resource resource;
    core->components.addComponent(star, resource);

    Hierarchy star_hierarchy;
    star_hierarchy.parents = { system };
    core->components.addComponent(star, star_hierarchy);

    Transform transform;
    core->components.addComponent(star, transform);

    core->components.addComponent(system, s_info);
    core->components.addComponent(system, resource);
    e_data.description = "an undefined solar system";
    e_data.name += " system";
    core->components.addComponent(system, e_data);

    return star;
}

void System_Generator::makePlanets(Entity system, Entity star, Hierarchy system_hierarchy)
{
    size_t count = prng::number(1, 17);

    system_hierarchy.children = { star };

    float orbital_radius = core->components.getComponent<Body_Info>(star).radius;

    constexpr static float radius_diff_min { 512.f };
    constexpr static float radius_diff_max { 2048.f };

    for (size_t i = 0; i < count; i++) {
        orbital_radius += prng::number(radius_diff_min, radius_diff_max);

        Entity body = core->entities.create();

        Signature sig;

        sig.set(toInt(Component::BODY_INFO));
        sig.set(toInt(Component::HIERARCHY));
        sig.set(toInt(Component::TRANSFORM));
        sig.set(toInt(Component::RESOURCE));
        sig.set(toInt(Component::ENTITY_DATA));

        core->entities.define(body, sig);

        std::string subtype = randomPlanet(star, orbital_radius);
        Body_Info min = planet_min[subtype];
        Body_Info max = planet_max[subtype];

        Entity_Data entity_info;
        entity_info.name = alphanumericName();
        entity_info.description = body_descriptions[subtype];
        core->components.addComponent(body, entity_info);

        Body_Info b_info;
        b_info.type = "planet";
        b_info.subtype = subtype;
        b_info.radius = prng::number(min.radius, max.radius);
        b_info.orbit = orbital_radius;
        b_info.temperature = prng::number(min.temperature, max.temperature);
        b_info.light = prng::number(min.light, max.light);
        b_info.color.r = prng::number(min.color.r, max.color.r);
        b_info.color.g = prng::number(min.color.g, max.color.g);
        b_info.color.b = prng::number(min.color.b, max.color.b);
        core->components.addComponent(body, b_info);

        Hierarchy b_hierarchy;
        b_hierarchy.parents = { system };
        core->components.addComponent(body, b_hierarchy);

        unsigned int point_count = std::pow(orbital_radius, .5) + 1;
        sf::CircleShape orbit(orbital_radius, point_count);

        Transform transform;
        unsigned int point = prng::number(orbit.getPointCount());
        transform.position = orbit.getPoint(point) - sf::Vector2f(orbital_radius, orbital_radius);
        core->components.addComponent(body, transform);

        orbital_radius += b_info.radius; // "clearing the neighborhood";

        system_hierarchy.children.push_back(body);

        makeResource(body);
    }

    Collision_Rect system_bounds;
    orbital_radius += 2000.f;
    system_bounds.setPosition(sf::Vector2f(-orbital_radius, -orbital_radius));
    system_bounds.setSize(sf::Vector2f(orbital_radius * 2.f, orbital_radius * 2.f));

    core->components.addComponent(system, system_bounds);

    core->components.addComponent(system, system_hierarchy);
}

void System_Generator::makeResource(Entity planet)
{
    Resource resource;

    auto& info = core->components.getComponent<Body_Info>(planet);
    std::string type = info.subtype;
    float radius = info.radius;

    // the checks should be removed once all pertinent data has been added to the database and is confirmed to work

    if (resource_chances.contains(type)) {
        for (auto& chance : resource_chances[type]) {
            if (prng::boolean(chance.second)) {
                if (resource_ranges.contains(type)) {
                    float min = resource_ranges[type].first.values[chance.first];
                    float max = resource_ranges[type].second.values[chance.first];
                    resource.set(chance.first, prng::number(min, max));
                }
                else {
                    std::cout << "failed to find resource range map for bodies of subtype " << type << "!\n";
                }
            }
        }
    }
    else {
        std::cout << "failed to find resource chance map for bodies of subtype " << type << "!\n";
    }
    core->components.addComponent(planet, resource);
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

    Body_Info star_info = core->components.getComponent<Body_Info>(star);

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
