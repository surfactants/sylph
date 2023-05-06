#include <game/system/system_manager.hpp>

#include <game/component/transform.hpp> // move to the context system when it's created

System_Manager::System_Manager()
{
    tile_system.switchContext = [&](Entity e) { context.set(Context::SOLAR, e); };
    solar_system.switchContext = [&](Entity e) { context.set(Context::GALACTIC, e); };

    accelerator.setMaxSpeed(10.f);
    accelerator.setAcceleration(1.f);
}

void System_Manager::update(const float delta_time)
{
    const sf::Vector2f mpos = relativeMousePos(*context.current_view);
    sf::Vector2f v = accelerator.update(delta_time);
    camera_controller.update(v);

    switch (context()) {
        case Context::GALACTIC:
            tile_system.update(mpos);
            break;
        case Context::SOLAR:
            solar_system.update(mpos);
    }
}
