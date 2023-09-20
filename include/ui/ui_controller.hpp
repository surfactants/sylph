#pragma once

#include "elements/element.hpp"

class UI_Controller {
public:
    UI_Controller(std::vector<Element*>& elements);

    void update(const sf::Vector2i& mpos);

    void setActive(Element* element);
    void unsetActive(Element* element);

    Element* moused { nullptr };
    Element* active { nullptr };

private:
    std::vector<Element*>& elements;
};
