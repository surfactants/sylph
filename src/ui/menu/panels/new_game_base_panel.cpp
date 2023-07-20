#include <ui/menu/panels/new_game_base_panel.hpp>

Base_Panel::Base_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize)
    : Panel(pos, size)
{
    // title
    std::string key { "BASE_TITLE" };
    std::string loc { localize(key) };

    title = std::make_shared<sf::Text>(loc, font, title_csize);
    localize.recordPersistent(key, title.get());
    addText(title.get(), Panel::LEFT, size.x);

    // elements
    const sf::Vector2f textbox_size(512.f, 96.f);

    player_name = std::make_shared<Simple_Textbox>("name", font, elem_csize);
    player_name->setSize(textbox_size);

    addElement(player_name.get(), Panel::LEFT);
}
