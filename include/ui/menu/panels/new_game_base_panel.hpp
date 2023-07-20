#pragma once

#include <ui/elements/elements.hpp>

class Base_Panel : public Panel {
public:
    Base_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize);

    std::shared_ptr<Simple_Textbox> player_name { nullptr };

protected:
    std::shared_ptr<sf::Text> title { nullptr };
};
