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
        case Component::COLLISION_RECT:
            addType(t, "MIN_X", "REAL", for_init);
            addType(t, "MIN_Y", "REAL", for_init);
            addType(t, "SIZE_X", "REAL", for_init);
            addType(t, "SIZE_Y", "REAL", for_init);
            break;
        case Component::ENTITY_DATA:
            addType(t, "NAME", "TEXT", for_init);
            addType(t, "DESCRIPTION", "TEXT", for_init);
            break;
        case Component::HIERARCHY:
            addType(t, "CHILDREN", "TEXT", for_init);
            addType(t, "PARENTS", "TEXT", for_init);
            addType(t, "NEIGHBORS", "TEXT", for_init);
            break;
        case Component::TRANSFORM:
            addType(t, "POS_X", "REAL", for_init);
            addType(t, "POS_Y", "REAL", for_init);
            addType(t, "ROTATION", "REAL", for_init);
            addType(t, "SCALE", "REAL", for_init);
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
        case Component::COLLISION_RECT:
            v += writeCollisionRect(e);
            break;
        case Component::ENTITY_DATA:
            v += writeEntityData(e);
            break;
        case Component::HIERARCHY:
            v += writeHierarchy(e);
            break;
        case Component::TRANSFORM:
            v += writeTransform(e);
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

std::string Component_Serializer::writeEntityData(Entity e)
{
    std::string v;
    auto t = getComponent<Entity_Data>(e);
    addValue(v, t.name);
    addValue(v, t.description);
    return v;
}

std::string Component_Serializer::writeHierarchy(Entity e)
{
    std::string v;
    auto t = getComponent<Hierarchy>(e);
    v += "'";
    for (const auto& it : t.children) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    v += "'";
    for (const auto& it : t.parents) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    v += "'";
    for (const auto& it : t.neighbors) {
        v += std::to_string(it) + ";";
    }
    v += "',";
    return v;
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
