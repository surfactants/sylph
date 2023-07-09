#include "home_panel.hpp"

Home_Panel::Home_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize)
    : Panel(pos, size)
{
    // title
    std::string text = "HOME_TITLE";
    std::string loc = localize(text);
    title = std::make_shared<sf::Text>(loc, font, title_csize);
    localize.recordPersistent(text, title.get());
    addText(title.get(), Panel::LEFT, size.x);

    const sf::Vector2f textbox_size(512.f, 96.f);

    // elements
    star_name = std::make_shared<Simple_Textbox>("STAR_NAME", font, elem_csize);
    star_name->setSize(textbox_size);
    addElement(star_name.get(), Panel::LEFT);

    homeworld_name = std::make_shared<Simple_Textbox>("HOMEWORLD_NAME", font, elem_csize);
    homeworld_name->setSize(textbox_size);
    addElement(homeworld_name.get(), Panel::LEFT);
}

void Home_Panel::reset()
{
    star_name->clear();
    homeworld_name->clear();
}
