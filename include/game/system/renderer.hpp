#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

/// Renderer ///
/// \brief game rendering system
/// creates layers for each view
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
    void add(size_t layer, sf::Drawable* d);

    void setLayer(size_t layer, sf::View* view);

    /// nullCheck ///
    /// \brief erases null pointers from the drawable container
    /// and erases the view layers
    ///
    void nullCheck();

    /// clear ///
    /// \brief erases all drawables
    void clear();

    void clearLayer(size_t layer);

private:
    struct Layer {
        sf::View* view { nullptr };
        std::vector<sf::Drawable*> drawables;
    };
    std::map<size_t, Layer> layers;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
