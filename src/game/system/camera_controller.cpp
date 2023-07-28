#include <game/system/camera_controller.hpp>

#include <game/component/transform.hpp>

Camera_Controller::Camera_Controller()
{
    name = "CAMERA_CONTROLLER";
}

void Camera_Controller::update(sf::Vector2f velocity, const sf::Vector2f& mpos)
{
    zoom();
    if (dragging) {
        if (drag_pos != mpos) {
            sf::Vector2f offset = drag_pos - mpos;
            move(offset);
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
    bounds = b;
    max_zoom = static_cast<int>(b.size.x / 1920.f);
    current_zoom = 1.f;
    zoom_speed = 0.f;
}

void Camera_Controller::move(sf::Vector2f velocity)
{
    sf::Vector2f vcenter = view->getCenter();
    sf::Vector2f vpos = vcenter + velocity;

    if (vpos.x < bounds.min.x) {
        velocity.x = bounds.min.x - vcenter.x;
    }
    else if (vpos.x > bounds.max.x) {
        velocity.x = bounds.max.x - vcenter.x;
    }

    if (vpos.y < bounds.min.y) {
        velocity.y = bounds.min.y - vcenter.y;
    }
    else if (vpos.y > bounds.max.y) {
        velocity.y = bounds.max.y - vcenter.y;
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

void Camera_Controller::endDrag(const sf::Vector2f&)
{
    dragging = false;
}

void Camera_Controller::setCenter(Entity e)
{
    const auto& transform = getComponent<Transform>(e);

    view->setCenter(transform.position);
}
