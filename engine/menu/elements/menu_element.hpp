#pragma once

#include <SFML/Graphics.hpp>

class Menu_Element : public sf::Transformable, public sf::Drawable {
public:
    enum State {
        UNAVAILABLE,
        READY,
        HIGHLIGHTED,
        ACTIVE,
        NULL_STATE
    };

    virtual bool update(const sf::Vector2i& mpos) = 0;
    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;
    virtual void setState(State state) { this->state = state; }
    virtual void keyPressed(sf::Keyboard::Key) {}
    virtual void clickRight() {}
    virtual void releaseRight() {}

    bool available() const
    {
        return (state != UNAVAILABLE);
    }

    bool highlighted() const
    {
        return (state == HIGHLIGHTED);
    }

    bool active() const
    {
        return (state == ACTIVE);
    }

    template <typename T>
    bool contains(const sf::Vector2<T> v) const
    {
        return frame.getGlobalBounds().contains(v.x, v.y);
    }

protected:
    sf::RectangleShape frame;
    State state { NULL_STATE };
    State base_state { NULL_STATE };
};
