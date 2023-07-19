#pragma once

#include <game/system/camera_controller.hpp>
#include <game/system/context.hpp>
#include <game/system/input_accelerator.hpp>
#include <game/system/renderer.hpp>

class System_Manager {
public:
    System_Manager();

    void windowResize(const sf::Vector2u& w_size);

    Camera_Controller camera_controller;

    Input_Accelerator accelerator;

    Renderer renderer;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    Context context { camera_controller, renderer };

    std::map<std::string, System*> map; // only holds systems with entities...
};
