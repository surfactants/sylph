# Key_String
*class*
*engine/input/key_string.hpp*

[Module Engine](../engine.md)  
[Submodule Input](input.md)

Handles conversions between sf::Keyboard::Key and std::string. A slight modification of the approach found in Bromeon's Thor library. The conversion maps themselves are static, and only defined when the class is first constructed.

## Public Member Functions
- std::string **toString( *const sf::Keyboard::Key& trigger* ):** converts the passed key to a string. Returns an empty string is no known conversion exists.
- sf::Keyboard::Key **toKey( *const std::string& str* ):** converts the passed string to a key. Returns sf::Keyboard::Unknown if no known conversion exists.