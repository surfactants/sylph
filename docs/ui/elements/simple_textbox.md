# Simple_Textbox
*class : [Element](element.md)*  
*ui/elements/simple_textbox.hpp*

## About
Textbox without highlighting or mouse cursor placement.

Also defines a set of macros for special unicode characters.

TODO finish function definitions

## Public Member Functions

### Simple_Textbox( *std::string title_text = "", bool sanitized = false* )

### void setFont( *const sf::Font& font* )

### void setMaxLength ( *unsigned int max_length* )

### unsigned int getMaxLength()

### virtual void textEntered( *const sf::Event& event* )

### virtual void keyPressed( *sf::Keyboard::Key key* )
Only used for arrow key parsing (left-right scrolling)

### void append( *sf::String addition* )
Adds the string to the end of the textbox, cutting off anything that doesn't fit.

### void backspace()
Erases the character before the cursor.

### void ctrlBackspace()
Deletes all characters up to (but not including\*) the first space before the cursor.

\* Multiple consecutive spaces will be deleted, leaving one.

### void clear()
Deletes all entered text.

### std::string getString()
Returns the inputted text

## Private Member Functions

### updateText()

---

[Module UI](../ui.md)  
[Submodule Elements](elements.md)  
[Return to Docs](../../docs.md)