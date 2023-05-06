#pragma once

#include <engine/resources/palette.hpp>
#include <engine/util/text.hpp>

#include <game/entity/entity.hpp>

#include "info_panel.hpp"

class System_Info : public Info_Panel {
public:
    System_Info()
    {
        frame.setFillColor(Palette::black);
        frame.setOutlineColor(Palette::white);
        frame.setOutlineThickness(2.f);
    }

    Entity entity;

    void clear()
    {
        sprites.clear();
        text.clear();
        //buttons.clear();
        entity = MAX_ENTITIES;
    }

    void addText(std::string str, unsigned int csize)
    {
        text.push_back(sf::Text(str, *font, csize));
        text.back().setFillColor(Palette::white);
    }

    void setText(sf::Vector2f offset)
    {
        sf::Vector2f pos = frame.getPosition() + offset;
        for (auto& t : text) {
            t.setPosition(pos);
            wrapText(t, frame.getSize().x - (offset.x * 2.f));
            pos.y += t.getGlobalBounds().top + t.getGlobalBounds().height + offset.y;
        }
    }

    void setSize(sf::Vector2f size)
    {
        frame.setSize(size);
    }
};
