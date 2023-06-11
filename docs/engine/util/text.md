# Text
*header*
*engine/util/text.hpp*

Functions for the manipulation of sf::Text objects

- void **centerText( *sf::Text& text* ):** centers text
- void **centerTextHorizontal( *sf::Text& text* ):** centers text along the x-axis
- void **centerTextVertical( *sf::Text& text* ):** centers text along the y-axis
- void **wrapText( *sf::Text& text, float width* ):** adds newline characters to the text until the object's x-size is <= width
- bool **charInBounds( *sf::Text& text, unsigned int character_index, float width* ):** determines whether or not the character's local x-position is within the provided width. for text wrapping.