#pragma once

#include <functional>
#include <map>
#include <type_traits> // is_same_v

#include <game/component/component.hpp>
#include <game/core/component_manager.hpp> // for component types

#include <game/core/entity.hpp>

// please don't tell anyone how i live

class Component_Serializer {
public:
    Component_Serializer() = default;

    static std::map<Component, std::string> to_string;
    static std::map<std::string, Component> to_component;

    std::string types(Component c, bool for_init);

    std::string values(Component c, Entity e);

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

private:
    void addType(std::string& sql, std::string name, std::string type, bool for_init)
    {
        sql += name;
        if (for_init) {
            sql += " " + type;
        }
        sql += ",";
    }

    template <typename T>
    void addValue(std::string& sql, T val)
    {
        if constexpr (std::is_same_v<std::string, T>) {
            sql += "'" + val + "'";
        }
        else {
            sql += std::to_string(val);
        }
        sql += ",";
    }
    std::string writeTransform(Entity e)
    {
        std::string v;
        auto t = getComponent<Transform>(e);
        addValue(v, t.position.x);
        addValue(v, t.position.y);
        addValue(v, t.rotation);
        addValue(v, t.scale);
        return v;
    }

    std::string writeCollisionRect(Entity e)
    {
        std::string v;
        auto t = getComponent<Collision_Rect>(e);
        addValue(v, t.min.x);
        addValue(v, t.min.y);
        addValue(v, t.max.x);
        addValue(v, t.max.y);
        addValue(v, t.size.x);
        addValue(v, t.size.y);
        return v;
    }

    std::string writePolygonTile(Entity e)
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

    std::string writeHierarchy(Entity e)
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

    std::string writeTile(Entity e)
    {
        std::string v;
        auto t = getComponent<Tile>(e);
        v += "'oops',";
        return v;
    }

    std::string writeEntityData(Entity e)
    {
        std::string v;
        auto t = getComponent<Entity_Data>(e);
        addValue(v, t.name);
        addValue(v, t.description);
        return v;
    }

    std::string writeBodyInfo(Entity e)
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

    std::string writeCivilizationData(Entity e)
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

    std::string writeResource(Entity e)
    {
        std::string v;
        auto t = getComponent<Resource>(e);
        v += "'oops',";
        return v;
    }
};
