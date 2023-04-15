#include <menu/state/menu.hpp>

std::unique_ptr<sf::Font> Menu::font { nullptr };

const sf::Vector2f Menu::button_start { sf::Vector2f(64.f, 64.f) };

std::function<void(Main_State::State)> Menu::setMainState;
std::function<void(Menu::State)> Menu::setMenuState;

sf::View Menu::view;

Menu_Element* Menu::moused_element { nullptr };
Menu_Element* Menu::active_element { nullptr };

Menu::Menu()
{
    if (!font) {
        font = std::make_unique<sf::Font>();
        font->loadFromFile("Abel.ttf");

        sf::Vector2f pos(0.f, 0.f);
        sf::Vector2f size(1920.f, 1080.f);
        sf::Vector2f wsize(1920.f, 1080.f);
        float xs = size.x / wsize.x;
        float ys = size.y / wsize.y;

        float xp = pos.x / wsize.x;
        float yp = pos.y / wsize.y;

        view.setViewport(sf::FloatRect(xp, yp, xs, ys));
        view.setSize(sf::Vector2f(wsize.x * xs, wsize.y * ys));
        view.setCenter(size / 2.f);

        Menu_Element::set_active = std::bind(setActive, std::placeholders::_1);
        Menu_Element::set_inactive = std::bind(unsetActive, std::placeholders::_1);
    }
}

void Menu::update(const sf::Vector2i& mpos)
{
    if (active_element) {
        if (active_element->update(mpos)) {
            moused_element = active_element;
            // successful update truncates update function
            // so elements overlaying others will not share input
            return;
        }
    }

    if (moused_element) {
        if (!moused_element->update(mpos)) {
            moused_element = nullptr;
        }
        else {
            return;
        }
    }

    for (auto& element : elements) {
        if (element->update(mpos)) {
            moused_element = element;
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
    else if (event.type == sf::Event::MouseWheelScrolled && moused_element) {
        moused_element->scroll(event.mouseWheelScroll.delta);
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
    if (moused_element && moused_element != active_element) {
        moused_element->clickLeft();
    }
}

void Menu::releaseLeft()
{
    if (active_element) {
        active_element->releaseLeft();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->releaseLeft();
    }
}

void Menu::clickRight()
{
    if (active_element) {
        active_element->clickRight();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->clickRight();
    }
}

void Menu::releaseRight()
{
    if (active_element) {
        active_element->releaseRight();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->releaseRight();
    }
}

void Menu::setActive(Menu_Element* element)
{
    active_element = element;
}

void Menu::unsetActive(Menu_Element* element)
{
    if (element == active_element) {
        active_element = nullptr;
    }
}

void Menu::addNav(std::string text, std::function<void()> target, Menu_Element::State base)
{
    nav.push_back(Button(text, *font, target, nav_csize, base));
}

void Menu::placeNav()
{
    sf::Vector2f pos = button_start;
    for (auto& n : nav) {
        n.setPosition(pos);
        pos.y += n.getSize().y + button_offset;
        elements.push_back(&n);
    }
}

void Menu::reset()
{
    if (moused_element) {
        moused_element->setToBase();
        moused_element = nullptr;
    }
    if (active_element) {
        active_element->deactivate();
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
    if (moused_element) {
        moused_element->deactivate();
        moused_element = nullptr;
    }
    if (active_element) {
        active_element->deactivate();
    }
    else {
        reset();
        std::visit(*this, escape_target);
    }
}

void Menu::clearNullElements()
{
    for (auto it = elements.begin(); it != elements.end();) {
        if (*it == nullptr) {
            elements.erase(it);
        }
        else {
            it++;
        }
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
