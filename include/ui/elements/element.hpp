#pragma once

#include <SFML/Graphics.hpp>

class Element : public sf::Drawable {
public:
    enum State {
        UNAVAILABLE,
        READY,
        HIGHLIGHTED,
        ACTIVE,
        NULL_STATE
    };

    static std::function<void(Element*)> setActive;
    static std::function<void(Element*)> setInactive;

    virtual void setPosition(const sf::Vector2f& position);

    const sf::RectangleShape& getFrame();

    virtual bool update(const sf::Vector2i& mpos) = 0;
    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;
    virtual void setState(State state);
    virtual void textEntered(const sf::Event& event);
    virtual void keyPressed(sf::Keyboard::Key);
    virtual void clickRight();
    virtual void releaseRight();

    virtual void scroll(float delta);

    virtual void deactivate();

    virtual void activate();

    bool available() const;

    bool highlighted() const;

    bool active() const;

    template <typename T>
    bool contains(const sf::Vector2<T> v) const
    {
        return frame.getGlobalBounds().contains(v.x, v.y);
    }

    virtual void setToBase();

protected:
    sf::RectangleShape frame;
    State state { NULL_STATE };
    State base_state { NULL_STATE };
};
