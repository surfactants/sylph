#include <game/system/context.hpp>

#include <game/component/transform.hpp>

Context::Context(Camera_Controller& camera, Renderer& renderer, Solar_System& solar, Tile_System& tile)
    : camera_controller { camera }
    , renderer { renderer }
    , solar_system { solar }
    , tile_system { tile }
{
}

void Context::toggle()
{
    switch (type) {
        case GALACTIC:
            set(SOLAR, last_system);
            break;

        case SOLAR:
            set(GALACTIC, last_system);
    }
}

void Context::set(Type t, Entity e)
{
    if (type == t) {
        return;
    }

    type = t;
    current_view = &view[t];
    camera_controller.view = current_view;

    renderer.clearLayer(0);
    renderer.setLayer(0, current_view);

    switch (t) {
        case GALACTIC:
            camera_controller.setBounds(world_bounds);
            resetView(Context::GALACTIC);

            if (last_system != MAX_ENTITIES) {
                current_view->setCenter(getComponent<Transform>(last_system).position);
            }

            renderer.add(0, &tile_system);
            break;

        case SOLAR:
            if (e == MAX_ENTITIES) {
                if (last_system != MAX_ENTITIES) {
                    e = last_system;
                }
                else {
                    break;
                }
            }
            else {
                last_system = e;
            }
            solar_system.load(e);

            camera_controller.setBounds(getComponent<Collision_Rect>(e));
            resetView(Context::SOLAR);

            current_view->setCenter(sf::Vector2f(0.f, 0.f));

            renderer.add(0, &solar_system);
            break;
    }
}

void Context::resetView(Type t)
{
    sf::Vector2f pos(0.f, 0.f);
    sf::Vector2f size(1920.f, 1080.f);
    sf::Vector2f wsize(1920.f, 1080.f);
    float xs = size.x / wsize.x;
    float ys = size.y / wsize.y;

    float xp = pos.x / wsize.x;
    float yp = pos.y / wsize.y;

    view[t].setViewport(sf::FloatRect(xp, yp, xs, ys));
    view[t].setSize(sf::Vector2f(wsize.x * xs, wsize.y * ys));
    view[t].setCenter(size / 2.f);
}
