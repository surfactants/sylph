#pragma once

#include "menu.hpp"

class Menu_Settings_General : public Menu {
public:
    Menu_Settings_General();

    virtual void save() override;

    static std::function<void(sf::Vector2u)> resizeWindow;

private:
    std::vector<Check_Box> check_boxes;
    Dropdown<sf::Vector2u> window_resizer;
};
