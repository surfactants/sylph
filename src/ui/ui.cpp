#include <ui/ui.hpp>

std::function<void(Game::State)> UI::setGameState;
std::function<void()> UI::openPause;

std::function<void(Main_State::State)> UI::setMainState;
std::function<void(UI::State)> UI::setUIState;

std::function<void()> UI::clearGame;

sf::View UI::view;

Localizer UI::localize;

void UI::grabElementActivity()
{
    Element::setActive = std::bind(&UI_Controller::setActive, &controller, std::placeholders::_1);
    Element::unsetActive = std::bind(&UI_Controller::unsetActive, &controller, std::placeholders::_1);
}

void UI::update(const sf::Vector2i& mpos)
{
    controller.update(mpos);
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
    else if (event.type == sf::Event::MouseWheelScrolled && controller.moused) {
        controller.moused->scroll(event.mouseWheelScroll.delta);
    }
    return controller.active;
}

bool UI::clickLeft()
{
    bool ret { false };
    if (controller.active) {
        ret = controller.active->clickLeft();
    }
    if (!ret && controller.moused && controller.moused != controller.active) {
        return controller.moused->clickLeft();
    }
    return ret;
}

bool UI::clickRight()
{
    if (controller.active) {
        return controller.active->clickRight();
    }
    if (controller.moused && controller.moused != controller.active) {
        return controller.moused->clickRight();
    }
    return false;
}

bool UI::releaseLeft()
{
    if (controller.active) {
        return controller.active->releaseLeft();
    }
    if (controller.moused && controller.moused != controller.active) {
        return controller.moused->releaseLeft();
    }
    return false;
}

bool UI::releaseRight()
{
    if (controller.active) {
        return controller.active->releaseRight();
    }
    if (controller.moused && controller.moused != controller.active) {
        return controller.moused->releaseRight();
    }
    return false;
}

bool UI::scroll(const float delta)
{
    if (controller.moused) {
        controller.moused->scroll(delta);
    }
    return (controller.moused);
}

bool UI::keyPressed(sf::Keyboard::Key key)
{
    if (controller.active) {
        return controller.active->keyPressed(key);
    }
    else if (key == sf::Keyboard::Escape) {
        bool ac = (controller.active);
        escape();
        return ac;
    }
    return false;
}

bool UI::textEntered(const sf::Event& event)
{
    if (controller.active) {
        return controller.active->textEntered(event);
    }
    return false;
}

void UI::setEscape(Main_State::State state)
{
    escape_target = state;
}

void UI::setEscape(UI::State state)
{
    if (controller.active) {
        controller.active->deactivate();
    }
    if (controller.moused) {
        controller.moused->setToBase();
    }
    escape_target = state;
}

void UI::escape()
{
    if (controller.moused) {
        controller.moused->deactivate();
        controller.moused = nullptr;
    }
    if (controller.active) {
        controller.active->deactivate();
    }
    else {
        reset();
        std::visit(*this, escape_target);
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
    if (controller.moused) {
        controller.moused->setToBase();
        controller.moused = nullptr;
    }
    if (controller.active) {
        controller.active->deactivate();
    }
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& element : elements) {
        target.setView(view);
        target.draw(*element, states);
    }
}
