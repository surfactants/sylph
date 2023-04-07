#pragma once

#include <menu/elements/check_box.hpp>

#include "menu.hpp"

class Menu_Settings_General : public Menu {
public:
    Menu_Settings_General();

    virtual void enterState() override;
    virtual void exitState() override;

private:
    std::vector<Check_Box> check_boxes;
};
