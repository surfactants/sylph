#pragma once

#include <map>
#include <memory>
#include <vector>

#include <game/component/component.hpp>
#include <game/entity/entity.hpp>

class Component_Manager {
public:
    Component_Manager();
    void clear();

    void registerEntity(const Entity e, std::vector<Component*> components);
    void deleteEntity(const Entity e);
    Component* getComponent(const Entity e, int component_type);

private:
    std::map<Entity, std::vector<std::unique_ptr<Component>>> signature;
    //std::map<Entity, std::unique_ptr<Derived_Component> derived;
};
