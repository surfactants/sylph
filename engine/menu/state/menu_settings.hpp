#pragma once

#include "menu.hpp"

class Menu_Settings : public Menu {
public:
    Menu_Settings();

    virtual void enterState() override;
    virtual void exitState() override;
};
