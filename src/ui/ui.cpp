#include <ui/ui.hpp>

std::function<void(Game::State)> UI::setGameState;
std::function<void()> UI::openPause;

std::function<void(Main_State::State)> UI::setMainState;
std::function<void(UI::State)> UI::setUIState;

std::function<void()> UI::clearGame;

sf::View UI::view;

Element* UI::moused { nullptr };
Element* UI::active { nullptr };

Localizer UI::localize;

UI::UI()
{
    // static initialization ensure this operation is only performed once
    static bool once = [&]() {
        Element::setActive = std::bind(setActive, std::placeholders::_1);
        Element::unsetActive = std::bind(unsetActive, std::placeholders::_1);
        return true;
    } (); // call it at definition end, but still in assignment of once
    (void) once; // override compiler warning re: unused variable
}

void UI::update(const sf::Vector2i& mpos)
{
    if (active) {
        if (active->update(mpos)) {
            moused = active;
            // still active, truncate
            return;
        }
    }

    if (moused) {
        if (!moused->update(mpos)) {
            moused = nullptr;
        }
        else {
            // still moused, truncate
            return;
        }
    }

    // check all elements
    for (auto& element : elements) {
        if (element->update(mpos)) {
            moused = element;
            break;
        }
    }
}

bool UI::handleInput(const sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                return clickLeft();
            case sf::Mouse::Right:
                return clickRight();
            default:
                break;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        switch (event.mouseButton.button) {
            case sf::Mouse::Left:
                return releaseLeft();
            case sf::Mouse::Right:
                return releaseRight();
            default:
                break;
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        return keyPressed(event.key.code);
    }
    else if (event.type == sf::Event::TextEntered) {
        return textEntered(event);
    }
    else if (event.type == sf::Event::MouseWheelScrolled && moused) {
        moused->scroll(event.mouseWheelScroll.delta);
    }
    return active;
}

bool UI::clickLeft()
{
    bool ret { false };
    if (active) {
        ret = active->clickLeft();
    }
    if (!ret && moused && moused != active) {
        return moused->clickLeft();
    }
    return ret;
}

bool UI::clickRight()
{
    if (active) {
        return active->clickRight();
    }
    if (moused && moused != active) {
        return moused->clickRight();
    }
    return false;
}

bool UI::releaseLeft()
{
    if (active) {
        return active->releaseLeft();
    }
    if (moused && moused != active) {
        return moused->releaseLeft();
    }
    return false;
}

bool UI::releaseRight()
{
    if (active) {
        return active->releaseRight();
    }
    if (moused && moused != active) {
        return moused->releaseRight();
    }
    return false;
}

bool UI::scroll(const float delta)
{
    if (moused) {
        moused->scroll(delta);
    }
    return (moused);
}

bool UI::keyPressed(sf::Keyboard::Key key)
{
    if (active) {
        return active->keyPressed(key);
    }
    else if (key == sf::Keyboard::Escape) {
        bool ac = (active);
        escape();
        return ac;
    }
    return false;
}

bool UI::textEntered(const sf::Event& event)
{
    if (active) {
        return active->textEntered(event);
    }
    return false;
}

void UI::setEscape(Main_State::State state)
{
    escape_target = state;
}

void UI::setEscape(UI::State state)
{
    if (active) {
        active->deactivate();
    }
    if (moused) {
        moused->setToBase();
    }
    escape_target = state;
}

void UI::escape()
{
    if (moused) {
        moused->deactivate();
        moused = nullptr;
    }
    if (active) {
        active->deactivate();
    }
    else {
        reset();
        std::visit(*this, escape_target);
    }
}

void UI::setActive(Element* element)
{
    if (active && active != element) {
        active->deactivate();
    }
    active = element;
}

void UI::unsetActive(Element* element)
{
    if (element == active) {
        active = nullptr;
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

    view.setViewport(sf::FloatRect(xp, yp, xs, ys));
    view.setSize(size);
    view.setCenter(size / 2.f);
}

void UI::clearNullElements()
{
    for (auto it = elements.begin(); it != elements.end();) {
        if (!(*it)) {
            elements.erase(it);
        }
        else {
            it++;
        }
    }
}

void UI::reset()
{
    if (moused) {
        moused->setToBase();
        moused = nullptr;
    }
    if (active) {
        active->deactivate();
    }
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
