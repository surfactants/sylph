#pragma once

#include <game/system/camera_controller.hpp>
#include <game/system/civilizations.hpp>
#include <game/system/context.hpp>
#include <game/system/input_accelerator.hpp>
#include <game/system/renderer.hpp>
#include <game/system/solar_system.hpp>
#include <game/system/tile_system.hpp>

class System_Manager {
public:
    System_Manager();

    void update(const float delta_time);
    void windowResize(const sf::Vector2u& w_size);

    Camera_Controller camera_controller;

    Input_Accelerator accelerator;

    Tile_System tile_system;
    Solar_System solar_system;

    Civilizations civilizations;

    Renderer renderer;

    static std::function<sf::Vector2f(sf::View)> relativeMousePos;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    Context context { camera_controller, renderer, solar_system, tile_system };

    std::map<std::string, System*> map;
};
