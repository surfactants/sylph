#include <game/system/tile_system.hpp>

#include <engine/math/collide.hpp>

#include <engine/util/prng.hpp>

void Tile_System::update(const sf::Vector2f& mpos)
{
    if (moused) {
        if (!collide::convexShape_Point(*moused, mpos)) {
            moused_frame.setOutlineThickness(0.f);
            moused = nullptr;
        }
        else {
            return;
        }
    }
    for (auto& t : tiles) {
        if (collide::convexShape_Point(t, mpos)) {
            moused = &t;
            moused_frame = t;
            moused_frame.setOutlineThickness(8.f);
        }
    }
}

void Tile_System::addTile(Entity e)
{
    entities.insert(e);
    auto tile = getComponent<Polygon_Tile>(e);
    const size_t n = tile.vertices.size();
    tiles.push_back(sf::ConvexShape(n));
    for (size_t i = 0; i < n; i++) {
        tiles.back().setPoint(i, tile.vertices[i]);
    }
    tiles.back().setFillColor(sf::Color::Transparent);
    tiles.back().setOutlineColor(Palette::white);
    tiles.back().setOutlineThickness(0.f);

    auto transform = getComponent<Transform>(e);
    constexpr float site_radius { 8.f };
    constexpr size_t site_points { 16 };
    sites.push_back(sf::CircleShape(site_radius, site_points));
    sites.back().setOrigin(sf::Vector2f(site_radius, site_radius));
    sites.back().setPosition(transform.position);
    int r = prng::number(145, 245);
    int g = prng::number(125, 225);
    int b = prng::number(145, 245);
    sites.back().setFillColor(sf::Color(r, g, b));
}

void Tile_System::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& t : tiles) {
        target.draw(t, states);
    }
    for (const auto& s : sites) {
        target.draw(s, states);
    }
    target.draw(moused_frame, states);
}
