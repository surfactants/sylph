#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/entity/entity.hpp>

#include "system.hpp"

class Solar_System : public System, public sf::Drawable {
public:
    Solar_System() = default;
    void load(Entity e);
    void clear();

    void update(const sf::Vector2f& mpos) {}

    std::function<void(Entity)> switchContext;

private:
    std::vector<std::pair<sf::CircleShape, Entity>> bodies;
    std::vector<sf::CircleShape> orbits;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
