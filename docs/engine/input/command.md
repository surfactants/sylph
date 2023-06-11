# Command
*POD struct*
*engine/input/command.md*

Stores information for determining keyboard input functions. Intended to bridge the gap between Database_Commands and the Input_Package (further mediated by **Game_State : Main_State**, which contains a lookup table for the string identifiers).

Also provides a sorting function, which simply sorts by press.

## Member Variables
- sf::Keyboard::Key **key**: determines which key activates the following functions
- std::string **press**: stores a string identifier for the function to be invoked when the preceding key is pressed
- std::string **release**: stores a string identifier for the function to be invoked when the preceding key is released