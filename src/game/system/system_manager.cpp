#include <game/system/system_manager.hpp>

void System_Manager::update(const float delta_time, const sf::Vector2f& mpos)
{
    accelerator.update(delta_time);
}
