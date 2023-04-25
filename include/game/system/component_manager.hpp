#pragma once

#include <map>
#include <memory>

#include <game/entity/entity.hpp>

class Component_Manager {
public:
    Component_Manager();
    void clear();

    void registerEntity(Entity e, Signature s);

private:
    //std::map<Entity, std::unique_ptr<Derived_Component> derived;

};
