#pragma once

#include <engine/util/text.hpp>

#include <game/core/entity.hpp>

#include "info_panel.hpp"

class System_Info : public Info_Panel {
public:
    System_Info();

    Entity entity;

    void clear();

    void addText(std::string str, unsigned int csize);

    void setText(sf::Vector2f offset);

    void setSize(sf::Vector2f size);
};
