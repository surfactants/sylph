#include <game/system/camera_controller.hpp>

void Camera_Controller::update(sf::Vector2f velocity)
{
    velocity *= (current_zoom * 2.f);
    sf::Vector2f vsize = view->getSize();
    sf::Vector2f vpos = view->getCenter() - (vsize / 2.f) + velocity;
    sf::Vector2f fpos = vpos + velocity;

    if (fpos.x <= bounds.min.x) {
        velocity.x = bounds.min.x - vpos.x;
    }
    else if (fpos.x + vsize.x > bounds.max.x) {
        velocity.x = bounds.max.x - (vpos.x + vsize.x);
    }

    if (fpos.y < bounds.min.y) {
        velocity.y = bounds.min.y - vpos.y;
    }
    else if (fpos.y + vsize.y > bounds.max.y) {
        velocity.y = bounds.max.y - (vpos.y + vsize.y);
    }

    view->move(velocity);
}

void Camera_Controller::zoom(float delta)
{
    float target;
    if (delta < 0.f && current_zoom < max_zoom) {
        // zoom out
        target = current_zoom + zoom_step;
    }
    else if (delta > 0.f && current_zoom > min_zoom) {
        // zoom in
        target = current_zoom - zoom_step;
    }
    else {
        return;
    }

    float factor = (target / current_zoom);
    view->zoom(factor);
    current_zoom *= factor;
}
