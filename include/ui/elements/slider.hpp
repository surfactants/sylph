#pragma once

#include <SFML/Graphics.hpp>

#include "element.hpp"

/// SLIDER ///
/// \brief Slider for settings menu.
///
class Slider : public Element {
public:
    Slider() = default;

    /// DEFAULT CONSTRUCTOR ///
    ///
    Slider(std::string ntitle, unsigned int title_size = 48);

    /// set ///
    /// \brief Prepares the bar.
    ///
    /// \param \b pos -> rects/texts.setPosition()
    /// \param \b font -> texts.setFont()
    ///
    void set(sf::Vector2f pos, const sf::Font& font);

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

    /// update ///
    /// \brief applies continual changes
    ///
    virtual bool update(const sf::Vector2i& mpos);

    /// clickLeft ///
    ///
    /// \brief activates continual changes if
    virtual bool clickLeft();

    /// releaseLeft ///
    ///
    /// \brief deactivates changing
    ///
    virtual bool releaseLeft();

    /// setFill ///
    /// \brief Sets the fill.
    ///
    /// \param \b f -> fill.setSize()
    ///
    void setFill(float f);

    virtual void setPosition(const sf::Vector2f& pos);

    virtual sf::Vector2f getSize() override;

    virtual void deactivate() override;

    float revert();
    void finalize();

    std::function<void(float)> fillChangeCallback { [](float){} };

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
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
