#pragma once

#include "component.hpp"

/// Drawable_Component ///
/// \brief provides SFML draw function
///
class Drawable_Component : public Component {
public:
    Drawable_Component() = delete;

protected:
    Drawable* drawable { nullptr };
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*drawable, states);
    }
};
