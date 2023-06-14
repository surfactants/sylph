#pragma once

#include <SFML/Graphics.hpp>

class Element : public sf::Drawable {
public:
    enum State {
        UNAVAILABLE,
        READY,
        HIGHLIGHTED,
        ACTIVE,
        SELECTED,
        NULL_STATE
    };

    Element() = default;

    virtual void setPosition(const sf::Vector2f& position);

    virtual void setState(State state);

    const sf::RectangleShape& getFrame() const;

    template <typename T>
    bool contains(const sf::Vector2<T> v) const
    {
        return frame.getGlobalBounds().contains(v.x, v.y);
    }

    bool available() const;
    bool highlighted() const;
    bool active() const;
    bool selected() const;

    virtual void activate();
    virtual void deactivate();

    static std::function<void(Element*)> setActive;
    static std::function<void(Element*)> unsetActive;

    virtual void select();
    virtual void deselect();

    static std::function<void(Element*)> setSelected;
    static std::function<void(Element*)> unsetSelected;

    virtual void setToBase();

    virtual bool update(const sf::Vector2i& mpos) = 0;

    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;

    virtual void clickRight();
    virtual void releaseRight();

    virtual void textEntered(const sf::Event& event);
    virtual void keyPressed(sf::Keyboard::Key key);

    virtual void scroll(float delta);

protected:
    sf::RectangleShape frame;
    State state { NULL_STATE };
    State base_state { NULL_STATE };
};
