#include <ui/menu/menu.hpp>

#include <engine/resources/font_manager.hpp>

sf::Font* Menu::font { Font_Manager::get(Font::MENU) };

const sf::Vector2f Menu::nav_start { sf::Vector2f(64.f, 64.f) };

Menu::Menu()
{
}

void Menu::addNav(std::string text, std::function<void()> target, Element::State base)
{
    std::string loc = localize(text);
    nav.push_back(std::make_unique<Button>(loc, *font, target, nav_csize, base));
    sf::Text* ptr = nav.back()->getText();
    localize.recordPersistent(text, ptr);
    elements.push_back(nav.back().get());
}

void Menu::placeNav()
{
    sf::Vector2f pos = nav_start;
    for (auto& n : nav) {
        n->setPosition(pos);
        pos.y += n->getSize().y + button_offset;
    }
}

void Menu::windowResize(const sf::Vector2u& w_size)
{
    setView(w_size);
    placeNav();
}
