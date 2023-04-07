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
    virtual void click() = 0;
    virtual void endClick() = 0;
    virtual void setState(State state) {}
    virtual void keyPressed(sf::Keyboard::Key) {}
    virtual void rightClick() {}
    virtual void endRightClick() {}

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
