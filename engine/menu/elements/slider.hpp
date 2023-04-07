#pragma once

#include <SFML/Graphics.hpp>

#include <resources/palette.hpp>

#include "menu_element.hpp"

/// SLIDER ///
/// \brief Slider for settings menu.
///
class Slider : public Menu_Element {
public:
    Slider() = default;

/// DEFAULT CONSTRUCTOR ///
///
    Slider(std::string ntitle);

/// set ///
/// \brief Prepares the bar.
///
/// \param \b pos -> rects/texts.setPosition()
/// \param \b font -> texts.setFont()
///
    void set(sf::Vector2f pos, sf::Font& font);

/// findFill ///
/// \brief Finds the fill by the mouse x position.
///
/// \param \b sf::Mouse::getPosition().x -> setFill()
///
    void findFill(int mX); //finds by mousepos

/// getFill ///
/// \brief Returns the fill as a percentage out of 100.
///
/// \return \b getFill() * 100.f
///
    float getFill() const;

/// SCROLL ///
/// \brief Changes the value by a fixed value.
///
/// \param \b delta -> setFill()
///
    void scroll(float delta);

/// checkMouse ///
/// \brief Checks to see if the mouse is inside the container,
/// for tracking change and scrolling.
///
/// \return \b true if mouse is inside container
///
    bool checkMouse(const sf::Vector2i& mpos);

/// update ///
/// \brief applies continual changes
///
    virtual bool update(const sf::Vector2i& mpos);

/// clickLeft ///
///
/// \brief activates continual changes if
    virtual void clickLeft();

/// releaseLeft ///
///
/// \brief deactivates changing
///
    virtual void releaseLeft();

/// setFill ///
/// \brief Sets the fill.
///
/// \param \b f -> fill.setSize()
///
    void setFill(float f);

    float revert();
    void finalize();

    std::function<void(float)> fillChangeCallback;

protected:
    sf::Text title; /**< Title label */
    sf::Text label; /**< On-container label */
    const static sf::Vector2f frame_size;

    sf::RectangleShape fill; /**< Slider */
    const static float offset; /**< Distance of slider from container */

    const static float scroll_factor; /**< Rate at which scrolling changes the fill */

    bool changing = false; /**< Tracking continual changes */

    bool moused = false;

    float start_fill { 100.f };

    float fill_factor { -100.f };

private:

/// draw ///
///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
