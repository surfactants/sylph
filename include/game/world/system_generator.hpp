#pragma once

#include <map>
#include <string>

#include <game/system/entity_manager.hpp>
#include <game/system/component_manager.hpp>

// transcluded from Database_Body:
//#include <engine/database/database_body.hpp>
using Resource_Chances = std::map<std::string, std::map<Resource::Type, float>>;
using Resource_Ranges = std::map<std::string, std::pair<Resource, Resource>>;

// looks like we'll have to pass the entity and component managers.....

class System_Generator {
public:
    System_Generator(Component_Manager& components, Entity_Manager& entities);

    void make(Entity system);

private:
    std::map<std::string, Body_Info> star_min;
    std::map<std::string, Body_Info> star_max;

    std::map<std::string, Body_Info> planet_min;
    std::map<std::string, Body_Info> planet_max;

    std::vector<std::pair<float, std::string>> star_chance;

    Component_Manager& components;
    Entity_Manager& entities;

    Entity makeStar(Entity system);
    void makePlanets(Entity system, Entity star);
    void makeResource(Entity planet);

    std::string randomStar();
    std::string randomPlanet(Entity star, float orbital_radius);
    std::string alphanumericName();

    std::map<std::string, std::string> body_descriptions;
    Resource_Chances resource_chances;
    Resource_Ranges resource_ranges;
};
