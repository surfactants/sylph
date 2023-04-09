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

    key_pressed[sf::Keyboard::Escape] = std::bind(&escape, this);

    key_pressed[sf::Keyboard::Left] = std::bind(&left, this);
    key_pressed[sf::Keyboard::Right] = std::bind(&right, this);
    key_pressed[sf::Keyboard::Up] = std::bind(&up, this);
    key_pressed[sf::Keyboard::Down] = std::bind(&down, this);
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

void Menu::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                clickLeft();
                break;
            case sf::Mouse::Right:
                clickRight();
                break;
            default:
                break;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                releaseLeft();
                break;
            case sf::Mouse::Right:
                releaseRight();
                break;
            default:
                break;
        }
    }
    else if (event.type == sf::Event::KeyPressed && key_pressed.contains(event.key.code)) {
        key_pressed[event.key.code]();
    }
    else if (active_textbox && event.type == sf::Event::TextEntered) {
        active_textbox->readText(event);
    }
}

void Menu::clickLeft()
{
    if (mouse_target) {
        mouse_target->clickLeft();
    }
    else if (active_textbox) {
        deactivateTextbox();
    }
}

void Menu::releaseLeft()
{
    if (mouse_target) {
        mouse_target->releaseLeft();
    }
}

void Menu::activateTextbox(Simple_Textbox* textbox)
{
    active_textbox = textbox;
}

void Menu::deactivateTextbox()
{
    if (active_textbox) {
        active_textbox->setState(Menu_Element::READY);
        active_textbox = nullptr;
    }
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

        elements.push_back(&n);
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
    if (active_textbox) {
        deactivateTextbox();
    }
    else {
        std::visit(*this, escape_target);
    }
}

void Menu::left()
{
    if (active_textbox) {
        active_textbox->scrollLeft();
    }
}

void Menu::right()
{
    if (active_textbox) {
        active_textbox->scrollRight();
    }
}

void Menu::up()
{}

void Menu::down()
{}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.draw(*element, states);
    }
}
