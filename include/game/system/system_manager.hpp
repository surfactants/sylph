#pragma once

#include "camera_controller.hpp"
#include "context.hpp"
#include "input_accelerator.hpp"
#include "renderer.hpp"
#include "solar_system.hpp"
#include "tile_system.hpp"

class System_Manager {
public:
    System_Manager();

    void update(const float delta_time);

    Camera_Controller camera_controller;

    Input_Accelerator accelerator;

    Tile_System tile_system;
    Solar_System solar_system;

    Renderer renderer;

    std::function<sf::Vector2f(sf::View)> relativeMousePos;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    Context context { camera_controller, renderer, solar_system, tile_system };

    void windowResize(const sf::Vector2u& w_size);
};
