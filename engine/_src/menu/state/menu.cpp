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
    if (active_element) {
        active_element->update(mpos);
        return;
    }

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
    else if (event.type == sf::Event::KeyPressed) {
        keyPressed(event.key.code);
    }
    else if (event.type == sf::Event::TextEntered) {
        textEntered(event);
    }
}
void Menu::textEntered(const sf::Event& event)
{
    if (active_element) {
        active_element->textEntered(event);
    }
}

void Menu::keyPressed(sf::Keyboard::Key key)
{
    if (active_element) {
        active_element->keyPressed(key);
    }
    else if (key == sf::Keyboard::Escape) {
        escape();
    }
}

void Menu::clickLeft()
{
    if (active_element) {
        active_element->clickLeft();
    }
    else if (mouse_target) {
        mouse_target->clickLeft();
    }
}

void Menu::releaseLeft()
{
    if (active_element) {
        active_element->releaseLeft();
    }
    else if (mouse_target) {
        mouse_target->releaseLeft();
    }
}

void Menu::clickRight()
{
    if (active_element) {
        active_element->clickLeft();
    }
    else if (mouse_target) {
        mouse_target->clickRight();
    }
}

void Menu::releaseRight()
{
    if (active_element) {
        active_element->releaseRight();
    }
    else if (mouse_target) {
        mouse_target->releaseRight();
    }
}

void Menu::setActive(Menu_Element* element)
{
    active_element = element;
}

void Menu::unsetActive()
{
    if (active_element) {
        active_element->setToBase();
        active_element = nullptr;
    }
}

void Menu::enterState()
{
    Menu_Element::set_active = std::bind(&Menu::setActive, this, std::placeholders::_1);
    Menu_Element::deactivate = std::bind(&Menu::unsetActive, this);
}

void Menu::exitState()
{
    unsetActive();
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
    if (active_element) {
            active_element->setState(Menu_Element::READY);
        active_element = nullptr;
    }
    escape_target = state;
}

void Menu::setEscape(Main_State::State state)
{
    escape_target = state;
}

void Menu::escape()
{
    if (active_element) {
        unsetActive();
    }
    else {
        std::visit(*this, escape_target);
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.draw(*element, states);
    }
}
