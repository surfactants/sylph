#include <ui/ui_hud.hpp>

UI_HUD::UI_HUD(System_Manager& systems)
{
    system_info.loadFont(font.get());
    systems.tile_system.activateUI = std::bind(loadSystemInfo, this, std::placeholders::_1);
    system_info.loadFont(font.get());
    system_info.setSize(sf::Vector2f(320.f, 1080.f - 4.f));
    system_info.setPosition(sf::Vector2f(1920.f - 322.f, 2.f));
    elements.push_back(&system_info);
}

void UI_HUD::loadSystemInfo(Entity e)
{
    if (e == MAX_ENTITIES) {
        system_info.clear();
    }
    else if (system_info.entity != e) {
        system_info.clear();
        auto info = getComponent<Entity_Info>(e);
        system_info.addText(info.name, 48);
        system_info.addText(info.description, 32);
        system_info.setText(sf::Vector2f(16.f, 16.f));
    }
}

void UI_HUD::enterState()
{
}

void UI_HUD::exitState()
{
}
