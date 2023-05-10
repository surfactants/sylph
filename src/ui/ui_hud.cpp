#include <ui/ui_hud.hpp>

UI_HUD::UI_HUD(System_Manager& systems)
{
    system_info.loadFont(font.get());
    systems.tile_system.activateUI = std::bind(loadSystemInfo, this, std::placeholders::_1);
    systems.solar_system.activateUI = std::bind(loadSystemInfo, this, std::placeholders::_1);
    system_info.loadFont(font.get());
    elements.push_back(&system_info);
    windowResize(sf::Vector2u(view.getSize()));
}

void UI_HUD::loadSystemInfo(Entity e)
{
    if (e == MAX_ENTITIES) {
        system_info.clear();
    }
    else if (system_info.entity != e) {
        system_info.clear();
        auto info = getComponent<Body_Info>(e);
        system_info.addText(info.name, 48);
        std::string classtype;
        if (info.type == "star" || info.type == "system") {
            classtype = info.subtype + "-Class Star";
        }
        else {
            classtype = info.subtype;
        }
        system_info.addText(classtype, 28);
        if (info.type == "system") {
            size_t child_count = getComponent<Hierarchy>(e).child.size();
            std::string count = std::to_string(child_count - 1);
            count += " planet";
            if (child_count != 1) {
                count += "s";
            }
            system_info.addText(count, 28);
        }
        else if (info.type == "star") {
            // hmmm...
        }
        system_info.addText(info.description, 24);
        system_info.setText(sf::Vector2f(16.f, 16.f));
    }
}

void UI_HUD::enterState()
{
}

void UI_HUD::exitState()
{
}

void UI_HUD::windowResize(const sf::Vector2u& w_size)
{
    float padding = system_info.getFrame().getOutlineThickness();
    sf::Vector2f sinfo_pos;
    sf::Vector2f sinfo_size;
    sinfo_size.x = 320.f;
    sinfo_size.y = w_size.y - (padding * 2.f);
    sinfo_pos.x = w_size.x - sinfo_size.x - padding;
    sinfo_pos.y = padding;
    system_info.setPosition(sinfo_pos);
    system_info.setSize(sinfo_size);
}
