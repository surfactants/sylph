#pragma once

#include <game/component/resource.hpp>

#include "element.hpp"

class Resource_Panel : public Element {
public:
    Resource_Panel();

    void read(const Resource& resource);

    void initialize(const Resource& resource, const sf::Font& font);

    void setPosition(sf::Vector2f position);

private:
    struct Cell {
        sf::Sprite sprite;
        sf::Text text;
    };

    std::vector<std::unique_ptr<Cell>> cells;

    std::map<Resource::Type, Cell*> cells_by_type;

    const sf::Texture& texture;

    const static sf::Vector2f icon_size;
    const static sf::Vector2f padding;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
