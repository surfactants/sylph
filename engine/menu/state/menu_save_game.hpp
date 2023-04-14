#pragma once

#include "menu.hpp"

class Menu_Save_Game : public Menu {
public:
    Menu_Save_Game();

    void start();
    void deleteSave();
    void cancel();

private:
    // add Scrollable savegame panel here (described in menu_load_game.hpp)
    // use obtained filename for writing
    // add confirmation dialog for overwriting
};
