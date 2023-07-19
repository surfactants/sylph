#include <game/core/system_manager.hpp>

#include <game/component/transform.hpp> // move to the context system when it's created

System_Manager::System_Manager()
{
    accelerator.setMaxSpeed(10.f);
    accelerator.setAcceleration(1.f);
}

void System_Manager::windowResize(const sf::Vector2u& w_size)
{
    context.setView(w_size);

    // TODO this is surely insufficient
}
