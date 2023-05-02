#pragma once

#include "camera_controller.hpp"
#include "input_accelerator.hpp"
#include "tile_renderer.hpp"

struct System_Manager {
    void update(const float delta_time, const sf::Vector2f& mpos);

    Camera_Controller camera_controller;

    Input_Accelerator accelerator;

    Tile_Renderer tile_renderer;
};
