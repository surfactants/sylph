#pragma once

#include "menu.hpp"

class Menu_Load_Game : public Menu {
public:
    Menu_Load_Game();

    virtual void enterState() override;
    virtual void exitState() override;

    void start();
    void deleteSave();
    void cancel();

private:
    // add another class ( : Scrollable) which finds a list of savegames
    // it should have a sort dropdown menu
    // it only needs to check for databases with filesystem, and then pass
    // the filenames back here for reading
};
