#pragma once

#include <SFML/Graphics.hpp>

#include "menu_element.hpp"

/// BUTTON ///
/// \brief Button class for mouse navigation.
///
class Button : public Menu_Element {
public:
    Button() = default;

    /// FULL CONSTRUCTOR ///
    /// \brief constructs the button, without a target
    ///
    Button(std::string nlabel, sf::Font& font, unsigned int csize, State base = READY);

    /// FULL CONSTRUCTOR WITH TARGET ///
    /// \brief constructs the button along with an onclick callback
    ///
    Button(std::string nlabel, sf::Font& font, std::function<void()> target, unsigned int csize, State base = READY);

    /// update ///
    /// \brief checks mouse highlight
    ///
    /// \brief true if highlighted
    ///
    virtual bool update(const sf::Vector2i& mpos) override;

    /// setPosition ///
    /// \brief places the frame and text
    ///
    void setPosition(sf::Vector2f pos);

    /// getPosition ///
    /// \brief returns the frame's position (centered)
    ///
    sf::Vector2f getPosition();

    void setSize(sf::Vector2f size);

    /// getSize ///
    /// \brief returns the frame's size
    ///
    sf::Vector2f getSize();

    std::string getLabel();

    /// clickLeft ///
    /// \brief returns true if button is available and highlighted. also calls target if applicable
    ///
    virtual void clickLeft() override;

    virtual void releaseLeft() override;

    std::function<void()> target; /**< onclick callback */

    void setState(Button::State state);

    void setLabel(std::string text);

protected:
    sf::Text label; /**< button text */

    /// draw ///
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    const static float padding; /**< space to be made in the frame around the label */
};
