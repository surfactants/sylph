#pragma once

#include "menu.hpp"

class Menu_Settings_Keymapper : public Menu {
public:
    Menu_Settings_Keymapper();

    virtual void enterState() override;
    virtual void exitState() override;
};
