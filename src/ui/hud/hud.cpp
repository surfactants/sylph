#include <ui/hud/hud.hpp>

#include <engine/resources/font_manager.hpp>

#include <engine/util/sfml_stream.hpp>

std::function<void(UI::State)> HUD::setHUDState;

System_Info HUD::system_info;

sf::Font* HUD::font { Font_Manager::get(Font::UI) };

HUD::HUD()
{}

void HUD::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
}

void HUD::initialize()
{
    system_info.loadFont(font);
}

void HUD::loadSystemInfo(Entity e)
{
    if (e == MAX_ENTITIES) {
        system_info.clear();
    }
    else if (system_info.entity != e) {
        system_info.clear();
        auto data = getComponent<Entity_Data>(e);
        auto info = getComponent<Body_Info>(e);
        system_info.addText(data.name, 48);
        std::string classtype;
        if (info.type == "star" || info.type == "system") {
            classtype = info.subtype + "-Class Star";
        }
        else {
            classtype = info.subtype;
        }
        system_info.addText(classtype, 28);

        if (info.type == "system") {
            size_t planet_count = getComponent<Hierarchy>(e).child.size() - 1;
            std::string count = std::to_string(planet_count);
            count += " planet";
            if (planet_count != 1) {
                count += "s";
            }
            system_info.addText(count, 28);
        }
        else if (info.type == "star") {
            // hmmm...
        }

        if (info.owned) {
            auto civilization = getComponent<Entity_Data>(info.owner);
            std::string own = "owned by " + civilization.name;
            system_info.addText(own, 28);
        }

        system_info.addText(data.description, 24);

        auto resource = getComponent<Resource>(e);

        for (auto& r : resource.values) {
            std::string r_text = Resource::toString(r.first);
            std::transform(r_text.begin() + 1, r_text.end(), r_text.begin() + 1, ::tolower);
            r_text += ": ";
            std::stringstream val;
            val << std::fixed << std::setprecision(1) << r.second;
            r_text += val.str();
            system_info.addText(r_text, 24);
        }

        system_info.setText(sf::Vector2f(16.f, 16.f));
    }
}

void HUD::enterState()
{}

void HUD::exitState()
{}

void HUD::windowResize(const sf::Vector2u& w_size)
{
    setView(w_size);
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
