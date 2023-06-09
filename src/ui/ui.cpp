#include <ui/ui.hpp>

#include <engine/resources/font_manager.hpp>

sf::Font* UI::font { Font_Manager::get(Font::UI) };

std::function<void(Game::State)> UI::setGameState;
std::function<void()> UI::openPause;

sf::View UI::view;

UI_Element* UI::moused_element { nullptr };
UI_Element* UI::active_element { nullptr };

UI::UI()
{
    if (active_element) {
        active_element->deactivate();
    }
    if (moused_element) {
        moused_element->setToBase();
    }

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

    UI_Element::setActive = std::bind(setActive, std::placeholders::_1);
    UI_Element::setInactive = std::bind(unsetActive, std::placeholders::_1);
}

void UI::update(const sf::Vector2i& mpos)
{
}

bool UI::handleInput(const sf::Event& event)
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
    return (moused_element || active_element);
}

void UI::clickLeft()
{
    if (active_element) {
        active_element->clickLeft();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->clickLeft();
    }
}

void UI::releaseLeft()
{
    if (active_element) {
        active_element->releaseLeft();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->releaseLeft();
    }
}

void UI::clickRight()
{
    if (active_element) {
        active_element->clickRight();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->clickRight();
    }
}

void UI::releaseRight()
{
    if (active_element) {
        active_element->releaseRight();
    }
    if (moused_element && moused_element != active_element) {
        moused_element->releaseRight();
    }
}

void UI::keyPressed(sf::Keyboard::Key key)
{
    if (active_element) {
        active_element->keyPressed(key);
    }
    else if (key == sf::Keyboard::Escape) {
        escape();
    }
}

void UI::textEntered(const sf::Event& event)
{
    if (active_element) {
        active_element->textEntered(event);
    }
}

void UI::escape()
{
}

void UI::setActive(UI_Element* element)
{
    active_element = element;
}

void UI::unsetActive(UI_Element* element)
{
    if (element == active_element) {
        active_element = nullptr;
    }
}

void UI::setView(const sf::Vector2u& w_size)
{
    sf::Vector2f pos(0.f, 0.f);
    sf::Vector2f size(w_size);
    float xs = 1.f;
    float ys = 1.f;

    float xp = 0.f;
    float yp = 0.f;

    sf::FloatRect vrect(xp, yp, xs, ys);
    sf::Vector2f center(size / 2.f);

    view.setViewport(vrect);
    view.setSize(size);
    view.setCenter(center);
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
