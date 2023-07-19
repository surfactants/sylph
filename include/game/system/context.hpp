#pragma once

#include <game/core/entity.hpp>

#include "system.hpp"

#include "camera_controller.hpp"
#include "renderer.hpp"

class Context : public System{
public:
    Context(Camera_Controller& camera, Renderer& renderer);

    enum Type {
        CONTEXT_ONE,
        CONTEXT_TWO
    };

    Type operator() ()
    {
        return type;
    }

    void toggle();

    void set(Type c, Entity e);

    Collision_Rect world_bounds;

    std::map<Type, sf::View> view {
        { CONTEXT_ONE, sf::View() },
        { CONTEXT_TWO, sf::View() }
    };

    sf::View* current_view { nullptr };

    void resetView(Type t);

    void setView(const sf::Vector2u& w_size);

    void setCenter(Entity e);

private:
    Type type;
    Camera_Controller& camera_controller;
    Renderer& renderer;

    sf::Vector2u w_size;

    Entity last_system { NULL_ENTITY };
};
