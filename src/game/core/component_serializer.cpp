#include <game/core/component_serializer.hpp>

std::map<Component, std::string> Component_Serializer::to_string;
std::map<std::string, Component> Component_Serializer::to_component;

std::string Component_Serializer::types(Component c, bool for_init)
{
    std::string t = "(ENTITY";
    if (for_init) {
        t += " INT PRIMARY KEY NOT NULL";
    }
    t += ",";
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
            addType(t, "SIZE_X", "REAL", for_init);
            addType(t, "SIZE_Y", "REAL", for_init);
            break;
        case Component::POLYGON_TILE:
            addType(t, "VERTICES", "TEXT", for_init);
            addType(t, "COLOR_R", "INT", for_init);
            addType(t, "COLOR_G", "INT", for_init);
            addType(t, "COLOR_B", "INT", for_init);
            addType(t, "COLOR_A", "INT", for_init);
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
            addType(t, "VAL", "TEXT", for_init);
            break;
    }
    if (t.back() == ',') {
        t.pop_back();
    }
    t += ")";
    return t;
}


std::string Component_Serializer::values(Component c, Entity e)
{
    std::string v = "("
                  + std::to_string(e)
                  + ",";
    switch (c) {
        default:
            break;
        case Component::TRANSFORM:
            v += writeTransform(e);
            break;
        case Component::COLLISION_RECT:
            v += writeCollisionRect(e);
            break;
        case Component::POLYGON_TILE:
            v += writePolygonTile(e);
            break;
        case Component::HIERARCHY:
            v += writeHierarchy(e);
            break;
        case Component::TILE:
            v += writeTile(e);
            break;
        case Component::ENTITY_DATA:
            v += writeEntityData(e);
            break;
        case Component::BODY_INFO:
            v += writeBodyInfo(e);
            break;
        case Component::CIVILIZATION_DATA:
            v += writeCivilizationData(e);
            break;
        case Component::RESOURCE:
            v += writeResource(e);
            break;
    }
    if (v.back() == ',') {
        v.pop_back();
    }
    v += ")";
    return v;
}

void Component_Serializer::addType(std::string& sql, std::string name, std::string type, bool for_init)
{
    sql += name;
    if (for_init) {
        sql += " " + type;
    }
    sql += ",";
}

std::string Component_Serializer::writeTransform(Entity e)
{
    std::string v;
    auto t = getComponent<Transform>(e);
    addValue(v, t.position.x);
    addValue(v, t.position.y);
    addValue(v, t.rotation);
    addValue(v, t.scale);
    return v;
}

std::string Component_Serializer::writeCollisionRect(Entity e)
{
    std::string v;
    auto t = getComponent<Collision_Rect>(e);
    addValue(v, t.min.x);
    addValue(v, t.min.y);
    addValue(v, t.size.x);
    addValue(v, t.size.y);
    return v;
}

std::string Component_Serializer::writePolygonTile(Entity e)
{
    std::string v;
    auto t = getComponent<Polygon_Tile>(e);
    v += "'";
    for (const auto& it : t.vertices) {
        v += std::to_string(it.x) + "," + std::to_string(it.y) + ";";
    }
    v += "',";
    addValue(v, t.color.r);
    addValue(v, t.color.g);
    addValue(v, t.color.b);
    addValue(v, t.color.a);
    return v;
}

std::string Component_Serializer::writeHierarchy(Entity e)
{
    std::string v;
    auto t = getComponent<Hierarchy>(e);
    v += "'";
    for (const auto& it : t.child) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    v += "'";
    for (const auto& it : t.parent) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    return v;
}

std::string Component_Serializer::writeTile(Entity e)
{
    std::string v;
    auto t = getComponent<Tile>(e);
    v += "'oops',";
    return v;
}

std::string Component_Serializer::writeEntityData(Entity e)
{
    std::string v;
    auto t = getComponent<Entity_Data>(e);
    addValue(v, t.name);
    addValue(v, t.description);
    return v;
}

std::string Component_Serializer::writeBodyInfo(Entity e)
{
    std::string v;
    auto t = getComponent<Body_Info>(e);
    addValue(v, t.type);
    addValue(v, t.subtype);
    addValue(v, t.radius);
    addValue(v, t.orbit);
    addValue(v, t.temperature);
    addValue(v, t.light);
    addValue(v, t.color.r);
    addValue(v, t.color.g);
    addValue(v, t.color.b);
    addValue(v, t.owned);
    addValue(v, t.owner);
    return v;
}

std::string Component_Serializer::writeCivilizationData(Entity e)
{
    std::string v;
    auto t = getComponent<Civilization_Data>(e);
    addValue(v, t.capital_system);
    addValue(v, t.homeworld);
    v += "'";
    for (const auto& it : t.systems) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    addValue(v, t.population);
    addValue(v, t.color.r);
    addValue(v, t.color.g);
    addValue(v, t.color.b);
    return v;
}

std::string Component_Serializer::writeResource(Entity e)
{
    std::string v = "'";
    auto r = getComponent<Resource>(e);
    for (const auto& t : r.values) {
        v += Resource::toString(t.first);
        v += ',';
        v += std::to_string(t.second);
        v += ";";
    }
    v += "'";
    return v;
}
