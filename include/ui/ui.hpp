#pragma once

#include <game/system/renderer.hpp>

class UI {
public:
    UI();

    Renderer* getRenderer();

private:
    static Renderer renderer;
};
