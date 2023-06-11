#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <map>
#include <string>

/// KEY_STRING ///
/// \brief This class handles conversions between sf::Keyboard::Key and std::string.
/// It is a modification of the solution in the Thor library by Bromeon
/// (uses two maps instead of a bimap)
///
class Key_String {
public:
    /// FULL CONSTRUCTOR ///
    /// \brief calls init() on first instancing
    ///
    Key_String();

    /// toString ///
    /// \brief converts key to string
    ///
    std::string toString(const sf::Keyboard::Key& trigger);

    /// toKey ///
    /// \brief converts string to key
    ///
    sf::Keyboard::Key toKey(const std::string& str);

private:
    static std::map<sf::Keyboard::Key, std::string> key_to_string; /**< conversion map, sf::Keyboard::Key to string */
    static std::map<std::string, sf::Keyboard::Key> string_to_key; /**< conversion map, string to sf::Keyboard::Key */

    /// init ///
    /// \brief loads string conversion maps
    ///
    void init();
};
