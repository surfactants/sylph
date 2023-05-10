#include <game/system/solar_system.hpp>

#include <engine/resources/palette.hpp>

#include <engine/math/collide.hpp>
#include <engine/math/primordial.hpp>

#include <game/component/body_info.hpp>
//#include <game/component/color.hpp>
#include <game/component/hierarchy.hpp>
#include <game/component/transform.hpp>

void Solar_System::load(Entity s)
{
    system = s;
    clear();
    auto c = getComponent<Hierarchy>(s).child;
    for (auto e : c) {
        entities.insert(e);
        auto transform = getComponent<Transform>(e);
        //auto color = getComponent<Color>(e);
        auto info = getComponent<Body_Info>(e);
        float r = info.radius;
        constexpr static size_t point_count { 30 };
        sf::CircleShape b(r, point_count); // radius, point count
        b.setOrigin(sf::Vector2f(r, r));
        b.setFillColor(info.color);
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

void Solar_System::update(const sf::Vector2f& mpos)
{
    // whatever
    if (moused) {
        if (!collide::contains(moused->first, mpos)) {
            if (moused != active) {
                moused->first.setOutlineThickness(0.f);
            }
            moused = nullptr;
        }
        else {
            return;
        }
    }
    for (auto& b : bodies) {
        auto& circle = b.first;
        if (collide::contains(circle, mpos)) {
            moused = &b;
            moused->first.setOutlineThickness(moused_border);
        }
    }
}

void Solar_System::clear()
{
    if (moused) {
        moused = nullptr;
    }
    if (active) {
        active = nullptr;
    }
    entities.clear();
    bodies.clear();
    orbits.clear();
}

void Solar_System::activate()
{
    if (moused && active != moused) {
        if (active) {
            active->first.setOutlineThickness(0.f);
        }
        active = moused;
        active->first.setOutlineThickness(active_border);
        activateUI(active->second);
    }
}

void Solar_System::deactivate()
{
    if (active) {
        if (active == moused) {
            active->first.setOutlineThickness(moused_border);
        }
        else {
            active->first.setOutlineThickness(0.f);
        }
        active = nullptr;
        activateUI(system);
    }
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
