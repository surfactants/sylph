#pragma once

#include "menu.hpp"

class Menu_Pause : public Menu {
public:
    Menu_Pause();

    virtual void enterState() override;
    virtual void exitState() override;
};
