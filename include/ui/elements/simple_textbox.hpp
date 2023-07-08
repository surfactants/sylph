#pragma once

#include <SFML/Graphics.hpp>

#include "element.hpp"

/// TEXTBOX ///

/** Example:
  *
  * Simple_Textbox textbox;
  * // the default color values set in the constructor exist in <resources/palette.hpp>
  * textbox.setFont(font); //takes a reference
  * textbox.setPosition(position); // takes sf::Vector2f
  * textbox.setSize(size); // takes sf::Vector2f
  *
 **/

// define unicode constants for reading text events
#define UNICODE_SELECT_ALL 1
#define UNICODE_COPY 3
#define UNICODE_BACKSPACE 8
#define UNICODE_RETURN 13
#define UNICODE_PASTE 22
#define UNICODE_CUT 24
#define UNICODE_ESCAPE 27
#define UNICODE_CTRL_BACKSPACE 127

/// \brief Container class for text input.
///
class Simple_Textbox : public Element {
public:
    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    Simple_Textbox(std::string title_text = "", bool sanitized = false);

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    Simple_Textbox(const std::string title_text, const sf::Font& font, const unsigned int title_size, bool sanitized = false);

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    void setFont(const sf::Font& font);

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    void setTitleSize(const unsigned int tcsize);

    ////////////////////////////////////////////////////////////
    /// \brief Changes the max length of the entered string.
    ///
    /// \param \b newMax -> maxLength
    ///
    /// \see getMaxLength()
    ///
    void setMaxLength(unsigned int max_length);

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
    virtual bool textEntered(const sf::Event& event) override;

    virtual bool keyPressed(sf::Keyboard::Key key) override;

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
    /// \see setSize(), totalSize()
    ///
    virtual sf::Vector2f getSize() override;

    ////////////////////////////////////////////////////////////
    /// \brief ...
    ///
    /// \see getPosition()
    ///
    virtual void setPosition(const sf::Vector2f& pos) override;

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

    virtual bool clickLeft() override;
    virtual bool releaseLeft() override;

    virtual bool releaseRight() override;

    virtual void activate() override;
    virtual void deactivate() override;

    bool empty();

    void setString(std::string tstr);

    void setOutline();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Sets the text object's string to entered_text.
    /// Internal, called whenever entered_text is updated.
    ///
    /// \see placeCursor()
    ///
    void updateText();

    sf::Text title;
    sf::Text text; /**< entered text*/

    sf::Text cursor; /**< Cursor text, '|'*/
    size_t max_length; /**< Maximum length of entered_text, default 32*/
    sf::Vector2f text_offset;

    size_t index { 0 }; /**< Cursor index */

    unsigned int text_size; /**< display_text font size, default 48*/

    std::string disallowed {};

    ////////////////////////////////////////////////////////////
    /// \brief Draws background, box, title, text, and cursor to the render target.
    ///
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
