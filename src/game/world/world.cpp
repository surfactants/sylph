#include <game/world/world.hpp>

#include <cassert>

#include <engine/math/collide.hpp>
#include <engine/util/prng.hpp>
#include <engine/util/sfml_stream.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

World::World()
{
}

void World::load(New_Game_Data data)
{
    size_t point_upper_bound;
    size_t point_lower_bound;

    float size_factor;

    switch (data.size) {
        case New_Game_Data::SMALL:
            point_lower_bound = 80;
            point_upper_bound = 120;
            size_factor = 4.f;
            break;
        case New_Game_Data::MEDIUM:
            point_lower_bound = 140;
            point_upper_bound = 180;
            size_factor = 6.f;
            break;
        case New_Game_Data::LARGE: // * 8
            point_lower_bound = 200;
            point_upper_bound = 250;
            size_factor = 8.f;
            break;
    }

    max = sf::Vector2f(1920.f, 1080.f);
    max *= size_factor;

    size_t point_count = prng::number(point_lower_bound, point_upper_bound);
    sf::Vector2<double> world_min(min);
    sf::Vector2<double> world_max(max.x, max.y);

    Voronoi::Diagram d(point_count, world_min, world_max);
    cells = d.get();
    std::cout << "loaded " << cells.size() << " cells\n";
    sites = d.sites();
    std::cout << "loaded " << sites.size() << " sites\n";
    // assert(cells.size() == sites.size());

    frame.setPosition(sf::Vector2f(min));
    frame.setSize(sf::Vector2f(max - min));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(5.f);
    frame.setOutlineColor(sf::Color::Red);

    min -= sf::Vector2f(512.f, 512.f);
    max += sf::Vector2f(512.f, 512.f);

    cells[prng::number(cells.size())].setFillColor(data.player_color);
}

void World::update(float delta_time, const sf::Vector2f& mpos)
{
    for (auto& cell : cells) {
        if (collide::convexShape_Point(cell, mpos)) {
            setMousedCell(&cell);
            break;
        }
    }
}

void World::activateCell()
{
    deactivateCell();
    if (moused_cell) {
        active_cell = moused_cell;
        active_cell->setOutlineThickness(active_thickness);
    }
}

void World::deactivateCell()
{
    if (active_cell) {
        if (active_cell == moused_cell) {
            active_cell->setOutlineThickness(moused_thickness);
        }
        else {
            active_cell->setOutlineThickness(0.f);
        }
        active_cell = nullptr;
    }
}

void World::unmouse()
{
    if (moused_cell) {
        if (moused_cell != active_cell) {
            moused_cell->setOutlineThickness(0.f);
        }
        moused_cell = nullptr;
    }
}

void World::setMousedCell(sf::ConvexShape* cell)
{
    unmouse();
    if (moused_cell != cell) {
        moused_cell = cell;
        if (moused_cell != active_cell) {
            moused_cell->setOutlineThickness(moused_thickness);
        }
    }
}

void World::eraseCell(unsigned int i)
{
    std::cout << "erasing site/cell " << i << '\n';
    if (i < cells.size()) {
        cells.erase(cells.begin() + i);
    }
    if (i < sites.size()) {
        sites.erase(sites.begin() + i);
    }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& c : cells) {
        target.draw(c, states);
    }
    for (const auto& s : sites) {
        target.draw(s, states);
    }
    target.draw(frame, states);
}
