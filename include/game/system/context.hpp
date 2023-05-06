#pragma once

#include <game/entity/entity.hpp>

#include "system.hpp"

#include "camera_controller.hpp"
#include "renderer.hpp"
#include "solar_system.hpp"
#include "tile_system.hpp"

class Context : public System{
public:
    Context(Camera_Controller& camera, Renderer& renderer, Solar_System& solar, Tile_System& tile);

    enum Type {
        GALACTIC,
        SOLAR
    };

    Type operator() ()
    {
        return type;
    }

    void toggle();

    void set(Type c, Entity e);

    Collision_Rect world_bounds;

    std::map<Type, sf::View> view {
        { GALACTIC, sf::View() },
        { SOLAR, sf::View() }
    };

    sf::View* current_view { nullptr };

    void resetView(Type t);

private:
    Type type { SOLAR };
    Camera_Controller& camera_controller;
    Renderer& renderer;
    Solar_System& solar_system;
    Tile_System& tile_system;

    Entity last_system { MAX_ENTITIES };
};
