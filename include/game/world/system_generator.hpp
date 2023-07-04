#pragma once

#include <map>
#include <string>

#include <game/core/ecs_core.hpp>

// transcluded from Database_Body:
//#include <engine/database/database_body.hpp>
using Resource_Chances = std::map<std::string, std::map<Resource::Type, float>>;
using Resource_Ranges = std::map<std::string, std::pair<Resource, Resource>>;

// looks like we'll have to pass the entity and component managers.....

class System_Generator {
public:
    System_Generator(ECS_Core* core);

    void make(Entity system, Hierarchy system_hierarchy);

private:
    std::map<std::string, Body_Info> star_min;
    std::map<std::string, Body_Info> star_max;

    std::map<std::string, Body_Info> planet_min;
    std::map<std::string, Body_Info> planet_max;

    std::vector<std::pair<float, std::string>> star_chance;

    ECS_Core* core;

    Entity makeStar(Entity system);
    void makePlanets(Entity system, Entity star, Hierarchy system_hierarchy);
    void makeResource(Entity planet);

    std::string randomStar();
    std::string randomPlanet(Entity star, float orbital_radius);
    std::string alphanumericName();

    std::map<std::string, std::string> body_descriptions;
    Resource_Chances resource_chances;
    Resource_Ranges resource_ranges;
};
