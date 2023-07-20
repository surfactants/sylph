#pragma once

#include <deque>
#include <memory>

#include <ui/strings/localizer.hpp>

#include "element.hpp"

class Panel : public Element {
public:
    enum Place {
        LEFT,
        CENTER,
        RIGHT
    };

    Panel();
    Panel(const sf::Vector2f pos, const sf::Vector2f size);

    virtual bool update(const sf::Vector2i& mpos);

    virtual void setPosition(const sf::Vector2f& pos);

    void setSize(const sf::Vector2f& size);

    void addElement(Element* element, const Place place);
    void addText(sf::Text* t, Place place, const float wrap_width);

    void clear();

    virtual bool clickLeft() override;
    virtual bool releaseLeft() override;

    virtual bool clickRight() override;
    virtual bool releaseRight() override;

    virtual bool textEntered(const sf::Event& event) override;
    virtual bool keyPressed(sf::Keyboard::Key key) override;

    virtual void deactivate() override;

    constexpr static float panel_padding { 16.f };

    constexpr static unsigned int elem_csize { 30 };
    constexpr static unsigned int title_csize { 50 };

    virtual void reset();

    sf::View* view { nullptr };

protected:
    sf::Vector2f left_pos;
    sf::Vector2f center_pos;
    sf::Vector2f right_pos;

    std::deque<Element*> elements;
    std::vector<sf::Text*> text;

    std::deque<sf::Drawable*> renderer;

    Element* active { nullptr };
    Element* moused { nullptr };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
