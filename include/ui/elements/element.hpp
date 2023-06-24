#pragma once

#include <SFML/Graphics.hpp>

#include <engine/resources/palette.hpp>

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

    constexpr static float padding { 8.f };
    constexpr static float outline { 2.f };

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

    virtual bool update(const sf::Vector2i&)
    {
        return false;
    }

    virtual bool clickLeft();
    virtual bool releaseLeft();

    virtual bool clickRight();
    virtual bool releaseRight();

    virtual bool textEntered(const sf::Event& event);
    virtual bool keyPressed(sf::Keyboard::Key key);

    virtual void scroll(float delta);

    virtual sf::Vector2f getPosition();
    virtual sf::Vector2f getSize();

protected:
    sf::RectangleShape frame;
    State state { NULL_STATE };
    State base_state { NULL_STATE };
};
