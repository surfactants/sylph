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
    const sf::Vector2f box_size(392.f, 96.f);

    homeworld_name = std::make_shared<Simple_Textbox>("HOMEWORLD_NAME", font, elem_csize);
    homeworld_name->setSize(textbox_size);
    addElement(homeworld_name.get(), Panel::LEFT);

    star_name = std::make_shared<Simple_Textbox>("STAR_NAME", font, elem_csize);
    star_name->setSize(textbox_size);
    addElement(star_name.get(), Panel::RIGHT);

    std::vector<std::pair<std::string, std::string>> drop_data = {
        { "O", "O" },
        { "B", "B" },
        { "A", "A" },
        { "F", "F" },
        { "G", "G" },
        { "K", "K" },
        { "M", "M" },
        { "D", "D" }
    };

    star_type = std::make_shared<Dropdown<std::string>>();
    star_type->setView(sf::Vector2f(0.f, 0.f), box_size, sf::Vector2u(1920, 1080));
    star_type->load(drop_data, font, elem_csize, 0);
    addElement(star_type.get(), Panel::RIGHT);
}

void Home_Panel::reset()
{
    star_name->clear();
    homeworld_name->clear();
}
