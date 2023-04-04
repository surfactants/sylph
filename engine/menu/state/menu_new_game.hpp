#pragma once

#include "menu.hpp"

class Menu_New_Game : public Menu {
public:
    Menu_New_Game();

    virtual void enterState() override;
    virtual void exitState() override;

    void start();
    void cancel();

private:
    // need a method for checking readiness
    // i.e. don't let a player start without a name, etc
};
