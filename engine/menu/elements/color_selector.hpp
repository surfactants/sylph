#pragma once

#include "menu_element.hpp"

////////////////////////////////////////////////////////////
/// \brief Color selection class
///
class Color_Selector : public Menu_Element {
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor. Creates the frame and slider,
    /// and places them at (16, 16)
    ///
    Color_Selector();

    ////////////////////////////////////////////////////////////
    /// \brief Sets hue to 0 and returns selector to start position.
    ///
    void reset();

    ////////////////////////////////////////////////////////////
    /// \brief Places selector and hue slider.
    ///
    /// \param pos top left position
    ///
    void setPosition(sf::Vector2f pos);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the selected color.
    ///
    /// \return selected_color
    ///
    sf::Color getColor();

    ////////////////////////////////////////////////////////////
    /// \brief Main event loop, checks for mouse pos, click, and release.
    ///
    /// \param event reference to event object created in main loop
    ///
    void readEvent(sf::Event& event);

    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void clickLeft() override;
    virtual void releaseLeft() override;
    virtual void clickRight() override;
    virtual void releaseRight() override;

    void setPreview(sf::Vector2f pos, sf::Vector2f size);

private:
    constexpr static unsigned int alpha { 255 };

    enum Moused {
        COLORS,
        SLIDER,
        PREVIEW,
        NONE
    };

    Moused moused { NONE };

    sf::VertexArray colors; /**<256x256 grid for HSV handling*/
        sf::RectangleShape selector; /**<Handle for color selection*/
        bool selecting { false }; /**<For tracking mouse events*/

    sf::VertexArray slider; /**<Hue selector*/
        sf::RectangleShape slider_handle; /**<Handle for hue selection*/
        bool sliding { false }; /**<For tracking mouse events*/

    sf::Color selected_color; /**<Tracks selected color*/
        sf::RectangleShape preview; /**<Example object*/

    ////////////////////////////////////////////////////////////
    /// \brief Places hue slider according to the mouse position,
    /// and calls setHue().
    /// Internal.
    ///
    /// \brief mousePos -> slider_handle.setPosition(), within bounds of slider
    ///
    void slide(sf::Vector2i mousePos);

    ////////////////////////////////////////////////////////////
    /// \brief Sets the frame to a new hue based on slider position,
    /// and recalls select().
    /// Internal.
    ///
    void setHue();

    ////////////////////////////////////////////////////////////
    /// \brief Places the selector.
    /// Internal.
    ///
    /// \param mousePos -> selector.setPosition(), within bounds of colors
    ///
    void select(sf::Vector2i mousePos);

    ////////////////////////////////////////////////////////////
    /// \brief Draws the frame, slider, and handles to the render target.
    /// Internal.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
