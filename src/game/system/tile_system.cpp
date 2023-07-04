#include <game/system/tile_system.hpp>

#include <engine/math/collide.hpp>

#include <engine/math/prng.hpp>

#include <game/component/polygon_tile.hpp>
#include <game/component/transform.hpp>
#include <game/component/body_info.hpp>
#include <game/component/hierarchy.hpp>

Tile_System::Tile_System()
{
    name = "TILE_SYSTEM";
}

void Tile_System::update(const sf::Vector2f& mpos)
{
    if (moused != NULL_ENTITY) {
        if (!collide::convexShape_Point(moused_frame, mpos)) {
            moused_frame.setOutlineThickness(0.f);
            moused = NULL_ENTITY;
        }
        else {
            return;
        }
    }
    const size_t n = tiles.size();
    for (size_t i = 0; i < n; i++) {
        if (collide::convexShape_Point(tiles[i], mpos)) {
            moused = tile_to_entity[i];
            moused_frame = tiles[i];
            moused_frame.setFillColor(sf::Color::Transparent);
            moused_frame.setOutlineThickness(moused_border);
        }
    }
}

void Tile_System::loadEntity(Entity e)
{
    entities.insert(e);
}

void Tile_System::setTileVisible(Entity e)
{
    if (entity_to_tile.contains(e)) {
        return;
    }

    setSiteVisible(e);

    const auto& tile = getComponent<Polygon_Tile>(e);
    const size_t n = tile.vertices.size();

    sf::ConvexShape shape(n);

    for (size_t i = 0; i < n; i++) {
        shape.setPoint(i, tile.vertices[i]);
    }

    shape.setOutlineColor(Palette::white);
    shape.setOutlineThickness(0.f);
    shape.setFillColor(tile.color);

    tiles.push_back(shape);

    const size_t tile_index = tiles.size() - 1;

    // update index maps
    if (entity_to_site.contains(e)) {
        const size_t site_index = entity_to_site[e];
        site_to_tile[site_index] = tile_index;
        tile_to_site[tile_index] = site_index;
    }

    entity_to_tile[e] = tile_index;
    tile_to_entity[tile_index] = e;

}

void Tile_System::setSiteVisible(Entity e)
{
    if (entity_to_site.contains(e)) {
        return;
    }

    const auto& transform = getComponent<Transform>(e);
    constexpr static float site_radius { 16.f };
    constexpr static size_t site_points { 16 };
    sf::CircleShape site(site_radius, site_points);
    site.setOrigin(sf::Vector2f(site_radius, site_radius));
    site.setPosition(transform.position);
    const auto& info = getComponent<Body_Info>(e);
    site.setFillColor(info.color);
    sites.push_back(site);

    const size_t site_index = sites.size() - 1;

    // update index maps
    if (entity_to_tile.contains(e)) {
        const size_t tile_index = entity_to_tile[e];
        site_to_tile[site_index] = tile_index;
        tile_to_site[tile_index] = site_index;
    }

    entity_to_site[e] = site_index;
    site_to_entity[site_index] = e;
}

Entity Tile_System::random()
{
    std::set<Entity>::iterator it = entities.begin();
    size_t offset = prng::number(entities.size());
    std::advance(it, offset);
    return *it;
}

void Tile_System::activate()
{
    const bool dbl = double_click();
    if (active != NULL_ENTITY && active == moused && dbl) {
        switchContext(active);
    }
    else if (moused != NULL_ENTITY && active != moused) {
        active = moused;
        active_frame = moused_frame;
        active_frame.setOutlineThickness(active_border);
        activateUI(active);
    }
}

void Tile_System::deactivate()
{
    if (active != NULL_ENTITY) {
        active = NULL_ENTITY;
        active_frame.setOutlineThickness(0.f);
        activateUI(NULL_ENTITY);
    }
}

void Tile_System::repaintTile(Entity e)
{
    if (entity_to_tile.contains(e)) {
        const size_t tile_index = entity_to_tile[e];
        const auto& color = getComponent<Polygon_Tile>(e).color;
        tiles[tile_index].setFillColor(color);
    }
}

void Tile_System::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& tile : tiles) {
        target.draw(tile, states);
    }
    for (const auto& site : sites) {
        target.draw(site, states);
    }
    for (const auto& l : lines) {
        target.draw(l, states);
    }
    target.draw(moused_frame, states);
    target.draw(active_frame, states);
}
