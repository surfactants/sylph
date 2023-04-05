#pragma once

#include <SFML/Window/Keyboard.hpp>

#include <string>

/// COMMAND ///
/// \brief wrapper class for game functions
///
struct Command {
    sf::Keyboard::Key k;
    std::string press;
    std::string release;
};
