#include <game/world/world.hpp>

#include <cassert>

#include <engine/math/collide.hpp>
#include <engine/util/prng.hpp>
#include <engine/util/sfml_stream.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

World::World(New_Game_Data data)
    : data { data }
{ }

std::vector<std::pair<Transform, Polygon_Tile>> World::polygonTiles()
{
    std::vector<std::pair<Transform, Polygon_Tile>> ptile;
    size_t point_upper_bound;
    size_t point_lower_bound;

    float size_factor;

    min = sf::Vector2f(0.f, 0.f);

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
    std::vector<sf::ConvexShape> cells = d.get();
    std::cout << "loaded " << cells.size() << " cells\n";
    std::vector<sf::Vector2f> sites = d.sites();
    std::cout << "loaded " << sites.size() << " sites\n";
    assert(cells.size() == sites.size() && "Cell count different from site count!");

    for (size_t i = 0; i < cells.size(); i++) {
        Transform transform;
        transform.position = sites[i];
        Polygon_Tile tile;
        size_t n = cells[i].getPointCount();
        for (size_t j = 0; j < n; j++) {
            tile.vertices.push_back(cells[i].getPoint(j));
        }
        ptile.push_back(std::make_pair(transform, tile));
    }

    min -= sf::Vector2f(512.f, 512.f);
    max += sf::Vector2f(512.f, 512.f);

    frame.setPosition(sf::Vector2f(min));
    frame.setSize(sf::Vector2f(max - min));

    cells[prng::number(cells.size())].setFillColor(data.player_color);

    return ptile;
}

std::vector<std::pair<sf::Vector2f, Tile>> tiles()
{
    return std::vector<std::pair<sf::Vector2f, Tile>>();
}
