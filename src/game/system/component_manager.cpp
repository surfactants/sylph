#include <game/system/component_manager.hpp>

Component_Manager::Component_Manager()
{
}

void Component_Manager::clear()
{
    signature.clear();
}

void Component_Manager::registerEntity(const Entity e, std::vector<Component*> components)
{
    if (signature.contains(e)) {
        // log this with information about the entity
        signature[e].clear();
    }

    for (auto& c : components) {
        signature[e].push_back(std::unique_ptr<Component>(c));
    }
}

void Component_Manager::deleteEntity(const Entity e)
{
    signature.erase(e);
}

Component* Component_Manager::getComponent(const Entity e, int component_type)
{
    if (!signature.contains(e) || component_type >= signature[e].size()) {
        // log this
        return nullptr;
    }
    return signature[e][component_type].get();
}
