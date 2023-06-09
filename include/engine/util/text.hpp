#pragma once

#include <SFML/Graphics/Text.hpp>

void centerText(sf::Text& text);

void centerTextVertical(sf::Text& text);

void centerTextHorizontal(sf::Text& text);

bool charInBounds(sf::Text& text, unsigned int i, float width);

void wrapText(sf::Text& text, float width);
