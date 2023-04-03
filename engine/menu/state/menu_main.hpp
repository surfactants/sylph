#pragma once

#include "menu.hpp"

class Menu_Main : public Menu {
public:
    Menu_Main();

    virtual void enterState() override;
    virtual void exitState() override;
};
