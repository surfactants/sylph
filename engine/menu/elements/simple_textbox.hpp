#pragma once

#include <SFML/Graphics.hpp>

#include "menu_element.hpp"

/// TEXTBOX ///

/** Example:
  *
  * Simple_Textbox textbox;
  * // the default color values set in the constructor exist in <resources/palette.hpp>
  * textbox.setFont(font); //takes a reference
  * textbox.setPosition(position); // takes sf::Vector2f
  * textbox.setSize(size); // takes sf::Vector2f
  *
  * the following two functions are engine callbacks for menu use.
  *
  * one sets the Simple_Textbox pointer in the Menu class to this:
  * textbox.setActive
  *
  * the other nulls that same pointer to indicate the object should stop receiving input:
  * textbox.clearActive
  *
  * they should be deprecated in favor of restoring genericity to element input
  *
 **/

/// \brief Container class for text input.
///
class Simple_Textbox : public Menu_Element {
private:
    sf::Text text; /**< entered text*/

    sf::Text cursor; /**< Cursor text, '|'*/
    size_t max_length; /**< Maximum length of entered_text, default 32*/
    sf::Vector2f text_offset;

    size_t index { 0 }; /**< Cursor index */

    unsigned int text_size; /**< display_text font size, default 48*/

public:

    std::function<void()> clearActive;
    std::function<void(Simple_Textbox*)> setActive;

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor.
    ///
    Simple_Textbox();

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    void setFont(sf::Font& font);

    ////////////////////////////////////////////////////////////
    /// \brief Draws background, box, title, text, and cursor to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    ////////////////////////////////////////////////////////////
    /// \brief Changes the max length of the entered string.
    ///
    /// \param \b newMax -> maxLength
    ///
    /// \see getMaxLength()
    ///
    void setMaxLength(unsigned int newMax);

    ////////////////////////////////////////////////////////////
    /// \brief Returns the max length of the entered string.
    ///
    /// \return maxLength
    ///
    /// \see setMaxLength()
    ///
    unsigned int getMaxLength();

    /// READ TEXT ///
    /// \brief Parses character to append from sf::Event.
    ///
    /// \param \b event -> append()
    ///
    /// \see append()
    ///
    void readText(const sf::Event& event);

    /// APPEND ///
    /// \brief Adds entered character to the end of the text.
    ///
    /// \param \b addition -> entered_text.push_back()
    ///
    /// \see readText()
    ///
    void append(sf::String addition);

    ////////////////////////////////////////////////////////////
    /// \brief Deletes the end character.
    ///
    /// \see ctrlBackspace(), clear()
    ///
    void backspace();

    ////////////////////////////////////////////////////////////
    /// \brief Deletes all characters up to the last space,
    /// excluding trailing spaces (which are also deleted).
    ///
    /// \see backspace(), clear()
    ///
    void ctrlBackspace();

    /// CLEAR ///
    /// \brief Deletes all entered text.
    ///
    /// \see backspace(), ctrlBackspace()
    ///
    void clear();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the inputted text as (std::string).
    ///
    /// \return entered_text
    ///
    /// \see
    ///
    std::string getString();

    ////////////////////////////////////////////////////////////
    /// \brief Sets the text object's string to entered_text.
    /// Internal, called whenever entered_text is updated.
    ///
    /// \see placeCursor()
    ///
    void updateText();

    ////////////////////////////////////////////////////////////
    /// \brief Changes the position of the cursor.
    /// Internal, primarily called by updateText().
    ///
    /// \see updateText()
    ///
    void placeCursor();

    ////////////////////////////////////////////////////////////
    /// \brief sets frame size
    ///
    /// \see getSize()
    ///
    void setSize(sf::Vector2f size);

    void scrollLeft();
    void scrollRight();

    ////////////////////////////////////////////////////////////
    /// \brief returns frame size
    ///
    /// \see setSize()
    ///
    sf::Vector2f getSize();

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    /// \see getPosition()
    ///
    void setPosition(sf::Vector2f pos);

    ////////////////////////////////////////////////////////////
    /// \brief Returns textbox position.
    ///
    /// \return box.getPosition()
    ///
    /// \see setPosition()
    ///
    sf::Vector2f getPosition();

    ////////////////////////////////////////////////////////////
    /// \brief Checks if the textbox contains the mouse, called
    /// on click for updating active.
    ///
    /// \return true if textbox contains mouse
    ///
    /// \see isActive(), activate(), deactivate()
    ///
    bool checkMouse(sf::Vector2i& mousePos);

    ////////////////////////////////////////////////////////////
    /// \brief Returns active state, used to determine whether
    /// or not text can be entered.
    ///
    /// \return bool active
    ///
    /// \see checkMouse(), activate(), deactivate()
    ///
    bool isActive();

    ////////////////////////////////////////////////////////////
    /// \brief Sets active = true.
    ///
    /// \see checkMouse(), isActive(), deactivate()
    ///
    void activate();

    ////////////////////////////////////////////////////////////
    /// \brief Sets active = false.
    ///
    /// \see checkMouse(), isActive(), activate()
    ///
    void deactivate();

    ////////////////////////////////////////////////////////////
    /// \brief Disables the translucent backdrop.
    ///
    void deactivateBackground();

    ////////////////////////////////////////////////////////////
    /// \brief Sets display_text font size.
    ///
    /// \param \b newPos -> textSize -> display_text.setCharacterSize()
    ///
    void setTextSize(const unsigned int size);

    virtual bool update(const sf::Vector2i& mpos) override;
    virtual void clickLeft() override;
    virtual void releaseLeft() override;

    virtual void releaseRight() override;

    bool empty();
};
