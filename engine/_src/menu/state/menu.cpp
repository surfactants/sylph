#include <menu/state/menu.hpp>

std::unique_ptr<sf::Font> Menu::font = nullptr;

const sf::Vector2f Menu::button_start = sf::Vector2f(64.f, 64.f);

std::function<void(Main_State::State)> Menu::setMainState;
std::function<void(Menu::State)> Menu::setMenuState;

Menu::Menu()
{
    if (!font) {
        font = std::make_unique<sf::Font>();
        font->loadFromFile("Abel.ttf");
    }
}

void Menu::update(const sf::Vector2i& mpos)
{
    if (mouse_target) {
        if (!mouse_target->update(mpos)) {
            mouse_target = nullptr;
        }
        else {
            return;
        }
    }

    for (auto& element : elements) {
        if (element->update(mpos)) {
            mouse_target = element;
            break;
        }
    }
}

void Menu::clickLeft()
{
    if (mouse_target) {
        mouse_target->clickLeft();
    }
}

void Menu::releaseLeft()
{
    if (mouse_target) {
        mouse_target->releaseLeft();
    }
}

void Menu::keyPressed(sf::Keyboard::Key k)
{}

void Menu::placeNav()
{
    sf::Vector2f pos = button_start;
    for (auto& n : nav) {
        sf::Vector2f size = n.getSize();
        pos.x += size.x / 2.f;
        pos.y += size.y / 2.f;
        n.setPosition(pos);
        pos.x -= size.x / 2.f;
        pos.y += size.y / 2.f;
        pos.y += button_offset;

        elements.push_back(&n);
    }
}

void Menu::placeSliders()
{
}

void Menu::setEscape(Menu::State state)
{
    escape_target = state;
}

void Menu::setEscape(Main_State::State state)
{
    escape_target = state;
}

void Menu::escape()
{
    std::visit(*this, escape_target);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.draw(*element, states);
    }
}
