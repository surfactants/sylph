#pragma once

#include "input_accelerator.hpp"
#include "tile_renderer.hpp"

struct System_Manager {
    void update(const float delta_time, const sf::Vector2f& mpos);

    Input_Accelerator accelerator;

    Tile_Renderer tile_renderer;
};
