#pragma once

#include "element.hpp"

class Panel : public Element {
public:
    Panel(const sf::Font& font);

    virtual void setPosition(const sf::Vector2f& position);

    void setSize(const sf::Vector2f& size);

    void setString(const std::string& string);

    sf::Text& getText();

private:
    sf::Text text;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
