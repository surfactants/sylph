#pragma once

#include <SFML/Graphics/Font.hpp>

#include <engine/resources/font.hpp>

/// FONT MANAGER ///
/// \brief singleton object that stores font objects and provides references to them
///
class Font_Manager {
public:

/// get ///
/// \brief returns a reference to the font keyed to the passed enumerated type
///
    static sf::Font* get(Font f);

private:
    std::map<Font, sf::Font> fonts; /**< font storage */

/// default constructor ///
/// \brief loads fonts from the database. private to enforce singleton behavior
///
    Font_Manager();

    static Font_Manager* instance; /**< singleton instance */
};
