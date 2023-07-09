#pragma once

#include <memory>
#include <string>

#include <ui/elements/elements.hpp>

#include <ui/strings/localizer.hpp>

class Civ_Panel : public Panel
{
public:
    Civ_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize);

    virtual void reset() override;

    std::shared_ptr<Simple_Textbox> name { nullptr };
    std::shared_ptr<Color_Selector> color;

protected:
    std::shared_ptr<sf::Text> title { nullptr };
};
