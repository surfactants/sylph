#pragma once

#include <functional>
#include <map>
#include <type_traits> // is_same_v

#include <game/component/component.hpp>
#include <game/core/components.hpp>

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
    void addType(std::string& sql, std::string name, std::string type, bool for_init);

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
    std::string writeTransform(Entity e);

    std::string writeCollisionRect(Entity e);

    std::string writePolygonTile(Entity e);

    std::string writeHierarchy(Entity e);

    std::string writeTile(Entity e);

    std::string writeEntityData(Entity e);

    std::string writeBodyInfo(Entity e);

    std::string writeCivilizationData(Entity e);

    std::string writeResource(Entity e);

    std::string writeDate(Entity e);
};
