#pragma once

#include <SFML/Graphics.hpp>

class Menu_Element : public sf::Transformable, public sf::Drawable {
public:
    enum State {
        UNAVAILABLE,
        READY,
        HIGHLIGHTED,
        ACTIVE
    };

    virtual bool update(const sf::Vector2i& mpos) = 0;
    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;
    virtual void setState(State state) { this->state = state; }
    virtual void keyPressed(sf::Keyboard::Key) {}
    virtual void clickRight() {}
    virtual void releaseRight() {}

    bool available()
    {
        return (state != UNAVAILABLE);
    }

    bool highlighted()
    {
        return (state == HIGHLIGHTED);
    }

    bool active()
    {
        return (state == ACTIVE);
    }

    template <typename T>
    bool contains(const sf::Vector2<T> v)
    {
        return frame.getGlobalBounds().contains(v.x, v.y);
    }

protected:
    sf::RectangleShape frame;
    State state;
    State base_state;
};
