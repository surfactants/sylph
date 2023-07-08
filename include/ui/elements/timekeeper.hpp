#pragma once

#include "element.hpp"

#include <ui/strings/localizer.hpp>

class Timekeeper : public Element {
public:
    Timekeeper(const sf::Font& font, Localizer& localize);

    void setYear(const unsigned int year);
    void setMonth(const unsigned int month);

    virtual void setPosition(const sf::Vector2f& position) override;

private:
    sf::Text year_label;
    sf::Text year;

    sf::Text month_label;
    sf::Text month;

    Localizer localize;

    constexpr static unsigned int csize { 32 };
    constexpr static unsigned int label_csize { 32 };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
