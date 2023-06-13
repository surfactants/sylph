#pragma once

#include "element.hpp"

class Check_Box : public Element {
public:
    Check_Box(sf::Font& font, std::string ls, unsigned int csize);
    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void setState(State state);

    void setChecked(bool state);
    void setPosition(sf::Vector2f pos);

    bool checked;

    constexpr static float stroke_default { 2.f };
    constexpr static float stroke_highlight { 4.f };

private:
    sf::Text label;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
