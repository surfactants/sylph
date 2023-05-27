#pragma once

#include "menu_element.hpp"
#include "toggle_scroller.hpp"

class Save_List : public Toggle_Scroller<std::string> {
public:
    Save_List(const sf::Font& font);

    void load();
};
