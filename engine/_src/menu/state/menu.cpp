#include <menu/state/menu.hpp>

std::unique_ptr<sf::Font> Menu::font = nullptr;

const sf::Vector2f Menu::button_start = sf::Vector2f(128.f, 64.f);

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
    for (auto& n : nav) {
        n.update(mpos);
    }
    for (auto& slider : sliders) {
        slider.update(mpos);
    }
}

bool Menu::clickLeft()
{
    for (auto& n : nav) {
        if (n.click()) {
            return true;
        }
    }

    for (auto& slider : sliders) {
        if (slider.click()) {
            return true;
        }
    }
    return false;
}

bool Menu::releaseLeft()
{
    for (auto& slider : sliders) {
        if (slider.unclick()) {
            return true;
        }
    }
    return false;
}

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
    }
}

void Menu::placeSliders()
{
    sf::Vector2f pos = button_start;
    pos.x += 256.f;
    for (auto& slider : sliders) {
        slider.set(pos, *font);
        pos.y += slider_offset;
    }
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
    for (const auto& n : nav) {
        target.draw(n, states);
    }
    for (const auto& slider : sliders) {
        target.draw(slider, states);
    }
}
