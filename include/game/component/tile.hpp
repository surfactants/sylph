#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>

struct Tile {
    sf::Texture* texture;
    sf::IntRect texture_rect;
};
