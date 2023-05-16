#include <game/system/tile_system.hpp>

#include <engine/math/collide.hpp>

#include <engine/util/prng.hpp>

#include <game/component/polygon_tile.hpp>
#include <game/component/transform.hpp>
#include <game/component/body_info.hpp>

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
            moused_frame.setFillColor(sf::Color::Transparent);
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
    //shape.setFillColor(tile.color);
    shape.setOutlineColor(Palette::white);
    shape.setOutlineThickness(0.f);

    // create site
    auto transform = getComponent<Transform>(e);
    constexpr float site_radius { 16.f };
    constexpr size_t site_points {16 };
    sf::CircleShape site(site_radius, site_points);
    site.setOrigin(sf::Vector2f(site_radius, site_radius));
    site.setPosition(transform.position);

    auto info = getComponent<Body_Info>(e);
    site.setFillColor(info.color);

    entities.insert(e);
    tiles.push_back(std::make_tuple(shape, site, e));

    size_t index = tiles.size() - 1;
    entity_to_index[e] = index;
    index_to_entity[index] = e;

    repaintTile(e);
}

Entity Tile_System::random()
{
    size_t index = prng::number(tiles.size());
    if (index_to_entity.contains(index)) {
        return index_to_entity[index];
    }
    return 0;
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

void Tile_System::repaintTile(Entity e)
{
    if (entity_to_index.contains(e)) {
        auto& shape = std::get<sf::ConvexShape>(tiles[entity_to_index[e]]);
        auto color = getComponent<Polygon_Tile>(e).color;
        shape.setFillColor(color);
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
