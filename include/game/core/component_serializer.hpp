#pragma once

#include <functional>
#include <map>

#include <game/component/component.hpp>

#include <game/entity/entity.hpp>

class Component_Serializer {
public:
    Component_Serializer() = default;

    static std::map<Component, std::string> to_string;
    static std::map<std::string, Component> to_component;

    std::string types(Component c, bool for_init);

    std::string values(Component c, Entity e);

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    //template <typename C>
    //std::string values(C c);

    void addType(std::string& sql, std::string name, std::string type, bool for_init)
    {
        sql += name;
        if (for_init) {
            sql += type;
        }
        sql += ",";
    }
};
