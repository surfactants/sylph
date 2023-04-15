#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>

/// COMMAND ///
/// \brief wrapper class for game functions
///
struct Command {
    sf::Keyboard::Key key;
    std::string press;
    std::string release;
};

inline bool commandSort(const Command& lhs, const Command& rhs)
{
    return (lhs.press < rhs.press);
}
