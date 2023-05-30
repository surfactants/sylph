#include <game/core/component_serializer.hpp>

std::map<Component, std::string> Component_Serializer::to_string;
std::map<std::string, Component> Component_Serializer::to_component;

std::string Component_Serializer::types(Component c, bool for_init)
{
    std::string t = "(ENTITY";
    if (for_init) {
        t += " INT PRIMARY KEY NOT NULL";
    }
    else {
        t += ")";
        return t;
    }
    t += ",";
    return t;
    switch (c) {
        default:
            break;
        case Component::TRANSFORM:
            addType(t, "POS_X", "REAL", for_init);
            addType(t, "POS_Y", "REAL", for_init);
            addType(t, "ROTATION", "REAL", for_init);
            addType(t, "SCALE", "REAL", for_init);
            break;
        case Component::COLLISION_RECT:
            addType(t, "MIN_X", "REAL", for_init);
            addType(t, "MIN_Y", "REAL", for_init);
            addType(t, "MAX_X", "REAL", for_init);
            addType(t, "MAX_Y", "REAL", for_init);
            addType(t, "SIZE_X", "REAL", for_init);
            addType(t, "SIZE_Y", "REAL", for_init);
            break;
        case Component::POLYGON_TILE:
            addType(t, "VERTICES", "TEXT", for_init);
            addType(t, "COLOR_R", "INT", for_init);
            addType(t, "COLOR_G", "INT", for_init);
            addType(t, "COLOR_B", "INT", for_init);
            addType(t, "COLOR_A", "INT", for_init);
            addType(t, "SIZE_Y", "REAL", for_init);
            break;
        case Component::HIERARCHY:
            addType(t, "CHILDREN", "TEXT", for_init);
            addType(t, "PARENTS", "TEXT", for_init);
            break;
        case Component::TILE:
            addType(t, "TODO", "TEXT", for_init);
            break;
        case Component::ENTITY_DATA:
            addType(t, "NAME", "TEXT", for_init);
            addType(t, "DESCRIPTION", "TEXT", for_init);
            break;
        case Component::BODY_INFO:
            addType(t, "TYPE", "TEXT", for_init);
            addType(t, "SUBTYPE", "TEXT", for_init);
            addType(t, "RADIUS", "REAL", for_init);
            addType(t, "ORBIT", "REAL", for_init);
            addType(t, "TEMPERATURE", "REAL", for_init);
            addType(t, "LIGHT", "REAL", for_init);
            addType(t, "COLOR_R", "INT", for_init);
            addType(t, "COLOR_G", "INT", for_init);
            addType(t, "COLOR_B", "INT", for_init);
            addType(t, "OWNED", "INT", for_init);
            addType(t, "OWNER", "INT", for_init);
            break;
        case Component::CIVILIZATION_DATA:
            addType(t, "CAPITAL", "INT", for_init);
            addType(t, "HOMEWORLD", "INT", for_init);
            addType(t, "SYSTEMS", "TEXT", for_init);
            addType(t, "POPULATION", "REAL", for_init);
            addType(t, "COLOR_R", "INT", for_init);
            addType(t, "COLOR_G", "INT", for_init);
            addType(t, "COLOR_B", "INT", for_init);
            break;
        case Component::RESOURCE:
            addType(t, "TODO", "TEXT", for_init);
            break;
    }
    t.pop_back();
    t += ")";
    return t;
}


std::string Component_Serializer::values(Component c, Entity e)
{
    std::string v = "("
                  + std::to_string(e)
                  + ")";
                  //+ ",";
    return v;
    switch (c) {
        default:
            break;
        case Component::TRANSFORM:
            //v += values<Transform>(getComponent<Transform>(e));
            break;
        case Component::COLLISION_RECT:
            break;
        case Component::POLYGON_TILE:
            break;
        case Component::HIERARCHY:
            break;
        case Component::TILE:
            break;
        case Component::ENTITY_DATA:
            break;
        case Component::BODY_INFO:
            break;
        case Component::CIVILIZATION_DATA:
            break;
        case Component::RESOURCE:
            break;
    }
    v += ")";
    return v;
}

/*
std::string Component_Serializer::values<Transform>(Transform t)
{
    return "bleh"
}
*/
