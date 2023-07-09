#pragma once

#include <memory>
#include <string>

#include <ui/elements/elements.hpp>

#include <ui/strings/localizer.hpp>

class Species_Panel : public Panel
{
public:
    Species_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize);

    virtual void reset() override;

    std::shared_ptr<Simple_Textbox> name { nullptr };
    std::shared_ptr<Dropdown<std::string>> biochemistry { nullptr };
    std::shared_ptr<Dropdown<std::string>> solvent { nullptr };
    std::shared_ptr<Slider> temperature { nullptr }; // optimal temperature slider, affected by biochemistry

protected:
    std::shared_ptr<sf::Text> title { nullptr };
};
