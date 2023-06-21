#pragma once

#include <SFML/Graphics/Color.hpp>

/// PALETTE ///
/// \brief stores colors for visual consistency
///
namespace Palette {
    // NEUTRAL
    const sf::Color black = sf::Color(10, 10, 10, 255); /**< darkest neutral */
    const sf::Color gray_dark = sf::Color(25, 25, 25, 255); /**< darker neutral */
    const sf::Color gray = sf::Color(90, 90, 90, 255); /**<mid-dark neutral */
    const sf::Color white = sf::Color(245, 245, 245, 255); /**< lightest neutral */

    // COLORS
    const sf::Color green = sf::Color(75, 125, 64, 255);
    const sf::Color blue = sf::Color(95, 75, 145, 255);
    const sf::Color purple = sf::Color(36, 10, 51, 255);
    const sf::Color orange = sf::Color(241, 126, 30, 255);
}
