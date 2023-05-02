#include <game/system/system_manager.hpp>

void System_Manager::update(const float delta_time, const sf::Vector2f& mpos)
{
    sf::Vector2f v = accelerator.update(delta_time);
    camera_controller.update(v);

    tile_system.update(mpos);
}
