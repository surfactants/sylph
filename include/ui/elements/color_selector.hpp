#pragma once

#include "element.hpp"

/// COLOR SELECTOR ///

/** Example:
  *
  * Color_Selector selector;
  * selector.setPreview(pos, size); // takes a reference
  * selector.setPosition(position); // takes sf::Vector2f
  *
 **/

/// \brief Color selection class
///
class Color_Selector : public Element {
public:
    ////////////////////////////////////////////////////////////
    /// \brief Default constructor. Creates the frame and slider,
    /// and places them at (16, 16)
    ///
    Color_Selector();

    Color_Selector(std::string title, const sf::Font& font);

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

    virtual bool clickLeft() override;
    virtual bool releaseLeft() override;
    virtual bool clickRight() override;
    virtual bool releaseRight() override;

    void setPreview(sf::Vector2f pos, sf::Vector2f size);

    virtual void deactivate() override;
    virtual void activate() override;

private:
    constexpr static unsigned int alpha { 255 };

    enum Moused {
        COLORS,
        SLIDER,
        PREVIEW,
        NONE
    };

    Moused moused { NONE };

    static bool initialized;

    static sf::VertexArray colors; /**<256x256 grid for HSV handling*/
    sf::RectangleShape selector; /**<Handle for color selection*/
    bool selecting { false }; /**<For tracking mouse events*/

    static sf::VertexArray slider; /**< Hue selector*/
    sf::RectangleShape slider_handle; /**< Handle for hue selection*/
    bool sliding { false }; /**< For tracking mouse events*/

    sf::RectangleShape preview; /**< Opens the selector and provides a preview of the color*/

    sf::Vector2f position;

    sf::Text label;

    void enactPosition();

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

    void initialize();
    void prepare();

    ////////////////////////////////////////////////////////////
    /// \brief Draws the frame, slider, and handles to the render target.
    /// Internal.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
