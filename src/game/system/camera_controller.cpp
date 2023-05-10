#include <game/system/camera_controller.hpp>

void Camera_Controller::update(sf::Vector2f velocity, const sf::Vector2f& mpos)
{
    zoom();
    if (dragging) {
        if (drag_pos != mpos) {
            sf::Vector2f offset = drag_pos - mpos;
            move(offset);
            drag_pos = mpos;
        }
    }
    else {
        velocity *= (current_zoom * zoom_speed_factor);
        move(velocity);
    }
}

void Camera_Controller::zoomImpulse(float delta)
{
    if (delta < 0.f) {
        zoom_speed += zoom_step;
        if (zoom_speed > max_speed) {
            zoom_speed = max_speed;
        }
    }
    else if (delta > 0.f) {
        zoom_speed -= zoom_step;
        if (zoom_speed < -max_speed) {
            zoom_speed = -max_speed;
        }
    }
}

void Camera_Controller::setBounds(Collision_Rect b)
{
    //b.setSize(b.size + sf::Vector2f(0.f, 322.f));
    bounds = b;
    max_zoom = static_cast<int>(b.size.x / 1920.f);
    current_zoom = 1.f;
    zoom_speed = 0.f;
}

void Camera_Controller::move(sf::Vector2f velocity)
{
    sf::Vector2f vsize = view->getSize() / current_zoom;
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

void Camera_Controller::zoom()
{
    if (zoom_speed == 0.f) {
        return;
    }
    bool stopping { false };
    float target = current_zoom + (zoom_speed * current_zoom);
    if (target < min_zoom) {
        target = min_zoom;
        stopping = true;
    }
    else if (target > max_zoom) {
        target = max_zoom;
        stopping = true;
    }

    float factor = (target / current_zoom);
    view->zoom(factor);
    current_zoom *= factor;

    if (stopping) {
        zoom_speed = 0.f;
        return;
    }
    else if (zoom_speed > 0.f) {
        zoom_speed -= zoom_decay + (zoom_speed * 0.04f);
        if (zoom_speed < 0.f) {
            zoom_speed = 0.f;
        }
    }
    else if (zoom_speed < 0.f) {
        zoom_speed += zoom_decay - (zoom_speed * 0.04f);
        if (zoom_speed > 0.f) {
            zoom_speed = 0.f;
        }
    }
}

void Camera_Controller::startDrag(const sf::Vector2f& mpos)
{
    dragging = true;
    drag_pos = mpos;
}

void Camera_Controller::endDrag(const sf::Vector2f& mpos)
{
    dragging = false;
}

void Camera_Controller::drag(const sf::Vector2f& mpos)
{
}
