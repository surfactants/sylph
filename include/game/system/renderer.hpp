#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

/// Renderer ///
/// \brief game rendering system
///

/*
  * FUNCTIONS:
  *
  * * Default constructor
  *
  * * void add(sf::Drawable* d)
  * > saves a
  *
  *
  *
  *
*/

class Renderer : public sf::Drawable {
public:
    Renderer() = default;

    /// add ///
    /// \brief stores a pointer to an sf::Drawable object.
    /// sorting/layering is not performed by this class.
    ///
    void add(sf::Drawable* d);

    /// nullCheck ///
    /// \brief erases null pointers from the drawable container
    /// iterative
    ///
    void nullCheck();

    /// clear ///
    /// \brief erases all drawables
    void clear();

private:
    std::vector<sf::Drawable*> drawables;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
