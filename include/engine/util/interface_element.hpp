#pragma once

#include <SFML/Graphics.hpp>

// MOVE THIS SOMEWHERE ELSE!!

class Interface_Element : public sf::Drawable {
public:
    enum State {
        UNAVAILABLE,
        READY,
        HIGHLIGHTED,
        ACTIVE,
        NULL_STATE
    };

    virtual void setPosition(const sf::Vector2f& position)
    {
        frame.setPosition(position);
    }

    const sf::RectangleShape& getFrame()
    {
        return frame;
    }

    virtual bool update(const sf::Vector2i& mpos) = 0;
    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;
    virtual void setState(State state)
    {
        this->state = state;
    }
    virtual void textEntered(const sf::Event& event) { }
    virtual void keyPressed(sf::Keyboard::Key) { }
    virtual void clickRight() { }
    virtual void releaseRight() { }

    virtual void scroll(float delta) { }

    virtual void deactivate() = 0;

    virtual void activate() = 0;

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

    virtual void setToBase()
    {
        setState(base_state);
    }

protected:
    sf::RectangleShape frame;
    State state { NULL_STATE };
    State base_state { NULL_STATE };
};
