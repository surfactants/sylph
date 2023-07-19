#include <game/system/context.hpp>

#include <game/component/transform.hpp>

Context::Context(Camera_Controller& camera, Renderer& renderer)
    : camera_controller { camera }
    , renderer { renderer }
{}

void Context::toggle()
{
    switch (type) {
        default:
            break;
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
        // set bounds for camera controller
        // call resetView
        // current_view->setCenter
        // add systems to the renderer
        default:
            break;
    }
}

void Context::resetView(Type t)
{
    setView(w_size);
}

void Context::setView(const sf::Vector2u& w_size)
{
    this->w_size = w_size;
    sf::Vector2f pos(0.f, 0.f);
    sf::Vector2f size(w_size);
    float xs = 1.f;
    float ys = 1.f;

    float xp = 0.f;
    float yp = 0.f;

    for (auto& v : view) {
        v.second.setViewport(sf::FloatRect(xp, yp, xs, ys));
        v.second.setSize(size);
        v.second.setCenter(size / 2.f);
    }
}
