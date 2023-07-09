#include <ui/menu/panels/civ_panel.hpp>

Civ_Panel::Civ_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize)
    : Panel(pos, size)
{
    // title
    std::string text = "CIV_TITLE";
    std::string loc = localize(text);
    title = std::make_shared<sf::Text>(loc, font, title_csize);
    localize.recordPersistent(text, title.get());
    addText(title.get(), Panel::LEFT, size.x);

    const sf::Vector2f textbox_size(512.f, 96.f);

    // elements
    name = std::make_shared<Simple_Textbox>("CIVILIZATION_NAME", font, elem_csize);
    name->setSize(textbox_size);
    addElement(name.get(), Panel::LEFT);

    color = std::make_shared<Color_Selector>("COLOR", font);
    addElement(color.get(), Panel::RIGHT);
}

void Civ_Panel::reset()
{
    name->clear();
    color->reset();
}
