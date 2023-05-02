#include <game/state/game_play.hpp>

Game_Play::Game_Play()
{
    systems.accelerator.setMaxSpeed(10.f);
    systems.accelerator.setAcceleration(1.f);

    sf::Vector2f pos(0.f, 0.f);
    sf::Vector2f size(1920.f, 1080.f);
    sf::Vector2f wsize(1920.f, 1080.f);
    float xs = size.x / wsize.x;
    float ys = size.y / wsize.y;

    float xp = pos.x / wsize.x;
    float yp = pos.y / wsize.y;

    map_view.setViewport(sf::FloatRect(xp, yp, xs, ys));
    map_view.setSize(sf::Vector2f(wsize.x * xs, wsize.y * ys));
    map_view.setCenter(size / 2.f);

    renderer.setLayer(0, &map_view);
    renderer.add(0, &systems.tile_system);

    current_view = &map_view;
    systems.camera_controller.view = &map_view;
}

Game_Play::~Game_Play()
{
    reset();
}

void Game_Play::update(float delta_time, const sf::Vector2f& mpos)
{
    systems.update(delta_time, mpos);
}

void Game_Play::clickLeft()
{ }

void Game_Play::releaseLeft()
{ }

void Game_Play::clickRight()
{ }

void Game_Play::releaseRight()
{ }
