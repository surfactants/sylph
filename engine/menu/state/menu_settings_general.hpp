#pragma once

#include "menu.hpp"

class Menu_Settings_General : public Menu {
public:
    Menu_Settings_General();

    virtual void enterState() override;
    virtual void exitState() override;
};
