#pragma once

#include "menu.hpp"

class Menu_Pause : public Menu {
public:
    Menu_Pause();

    static std::function<void()> clearGame;
};
