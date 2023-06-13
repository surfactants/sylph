#pragma once

#include "element.hpp"

class Info_Panel : public Element {
public:
    Info_Panel();

    void loadFont(sf::Font* font);

    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void clickLeft() override;
    virtual void releaseLeft() override;

protected:
    sf::Font* font;
    std::vector<sf::Sprite> sprites;
    std::vector<sf::Text> text;
    //std::vector<Button> buttons;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
