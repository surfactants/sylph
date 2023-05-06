#include <game/system/tile_system.hpp>

#include <engine/math/collide.hpp>

#include <engine/util/prng.hpp>

#include <game/component/color.hpp>
#include <game/component/polygon_tile.hpp>
#include <game/component/transform.hpp>
#include <game/component/entity_info.hpp>

void Tile_System::update(const sf::Vector2f& mpos)
{
    if (moused) {
        if (!collide::convexShape_Point(moused_frame, mpos)) {
            moused_frame.setOutlineThickness(0.f);
            moused = nullptr;
        }
        else {
            return;
        }
    }
    for (auto& t : tiles) {
        auto& shape = std::get<sf::ConvexShape>(t);
        if (collide::convexShape_Point(shape, mpos)) {
            moused = &t;
            moused_frame = shape;
            moused_frame.setOutlineThickness(moused_border);
            break;
        }
    }
}

void Tile_System::addTile(Entity e)
{
    // create shape
    auto tile = getComponent<Polygon_Tile>(e);
    const size_t n = tile.vertices.size();
    sf::ConvexShape shape(n);
    for (size_t i = 0; i < n; i++) {
        shape.setPoint(i, tile.vertices[i]);
    }
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(Palette::white);
    shape.setOutlineThickness(0.f);

    // create site
    auto transform = getComponent<Transform>(e);
    constexpr float site_radius { 8.f };
    constexpr size_t site_points { 16 };
    sf::CircleShape site(site_radius, site_points);
    site.setOrigin(sf::Vector2f(site_radius, site_radius));
    site.setPosition(transform.position);

    auto color = getComponent<Color>(e);
    site.setFillColor(color);

    entities.insert(e);
    tiles.push_back(std::make_tuple(shape, site, e));
}

void Tile_System::activate()
{
    const bool dbl = double_click();
    if (active && active == moused && dbl) {
        switchContext(std::get<Entity>(*active));
        return;
    }
    if (moused && active != moused) {
        active = moused;
        active_frame = moused_frame;
        active_frame.setOutlineThickness(active_border);
        activateUI(std::get<Entity>(*active));
    }
}

void Tile_System::deactivate()
{
    if (active) {
        active = nullptr;
        active_frame.setOutlineThickness(0.f);
        activateUI(MAX_ENTITIES);
    }
}

void Tile_System::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& s : tiles) {
        target.draw(std::get<sf::ConvexShape>(s));
        target.draw(std::get<sf::CircleShape>(s));
    }
    target.draw(moused_frame, states);
    target.draw(active_frame, states);
}
