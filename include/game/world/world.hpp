#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include <game/data/new_game_data.hpp>

class World : public sf::Drawable {
public:
    World();

    void load(New_Game_Data data);

    void update(float delta_time, const sf::Vector2f& mpos);

    void activateCell();
    void deactivateCell();
    void unmouse();

    void eraseCell(unsigned int i = 0);

    sf::Vector2f min { 0.f, 0.f };
    sf::Vector2f max { 1920.f * 5.f, 1080.f * 5.f };

private:
    std::vector<sf::ConvexShape> cells;
    std::vector<sf::RectangleShape> sites;

    sf::ConvexShape* moused_cell { nullptr };
    sf::ConvexShape* active_cell { nullptr };

    constexpr static float moused_thickness { 2.f };
    constexpr static float active_thickness { 4.f };

    void setMousedCell(sf::ConvexShape* cell);

    sf::RectangleShape frame;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
