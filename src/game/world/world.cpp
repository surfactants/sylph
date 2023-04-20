#include <game/world/world.hpp>

#include <engine/util/prng.hpp>

#include <game/world/gen/voronoi/diagram.hpp>

#include <engine/util/sfml_stream.hpp>

World::World()
{
    size_t point_count = prng::number(20, 40);
    sf::Vector2<double> min(0.d, 0.d);
    sf::Vector2<double> max(1920.d, 1080.d);

    Voronoi::Diagram d(point_count, min, max);
    cells = d.get();
    sites = d.sites();

    frame.setSize(sf::Vector2f(max));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineThickness(5.f);
    frame.setOutlineColor(sf::Color::Red);
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
