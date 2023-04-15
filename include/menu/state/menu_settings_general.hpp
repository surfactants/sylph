#pragma once

#include "menu.hpp"

class Menu_Settings_General : public Menu {
public:
    Menu_Settings_General();

    virtual void save() override;

private:
    std::vector<Check_Box> check_boxes;
    Dropdown<int> dropdown;
};
