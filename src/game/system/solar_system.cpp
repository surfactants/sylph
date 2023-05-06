#include <game/system/solar_system.hpp>

#include <engine/resources/palette.hpp>

#include <engine/math/primordial.hpp>

#include <game/component/body_info.hpp>
#include <game/component/color.hpp>
#include <game/component/hierarchy.hpp>
#include <game/component/transform.hpp>

void Solar_System::load(Entity s)
{
    clear();
    auto c = getComponent<Hierarchy>(s).child;
    for (auto e : c) {
        entities.insert(e);
        auto transform = getComponent<Transform>(e);
        auto color = getComponent<Color>(e);
        auto info = getComponent<Body_Info>(e);
        float r = info.radius;
        constexpr static size_t point_count { 30 };
        sf::CircleShape b(r, point_count); // radius, point count
        b.setOrigin(sf::Vector2f(r, r));
        b.setFillColor(color);
        b.setPosition(transform.position);
        bodies.push_back(std::make_pair(b, e));

        unsigned int orbit_points = roundFloat(info.orbit / 2.f); // find a better way to calculate this, with a ceiling

        orbits.push_back(sf::CircleShape(info.orbit, orbit_points));
        orbits.back().setOrigin(sf::Vector2f(info.orbit, info.orbit));
        orbits.back().setFillColor(sf::Color::Transparent);
        orbits.back().setOutlineColor(Palette::white);
        orbits.back().setOutlineThickness(4.f);
    }
}

void Solar_System::clear()
{
    entities.clear();
    bodies.clear();
    orbits.clear();
}

void Solar_System::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& o : orbits) {
        target.draw(o, states);
    }
    for (const auto& b : bodies) {
        target.draw(b.first, states);
    }
}
