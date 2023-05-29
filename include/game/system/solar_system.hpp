#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/entity/entity.hpp>

#include "system.hpp"

class Solar_System : public System, public sf::Drawable {
    typedef std::pair<sf::CircleShape, Entity> Body;

public:
    Solar_System();
    void load(Entity e);
    void clear();

    void update(const sf::Vector2f& mpos);

    void activate();
    void deactivate();

    std::function<void(Entity)> activateUI;
    std::function<void(Entity)> switchContext;

    Body* active;

private:
    std::vector<Body> bodies;
    std::vector<sf::CircleShape> orbits;

    Body* moused;

    Entity system;

    constexpr static float moused_border { 4.f };
    constexpr static float active_border { 8.f };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
