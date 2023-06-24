#include <ui/hud/hud.hpp>

#include <engine/resources/font_manager.hpp>

#include <engine/util/sfml_stream.hpp>

#include <game/component/resource.hpp>

sf::Font* HUD::font { Font_Manager::get(Font::UI) };

std::function<void(UI::State)> HUD::setHUDState;

std::unique_ptr<System_Info> HUD::system_info { nullptr };

std::unique_ptr<Resource_Panel> HUD::resource_panel { nullptr };

std::unique_ptr<Panel> HUD::turn_panel { nullptr };

std::unique_ptr<Timekeeper> HUD::timekeeper  { nullptr };

HUD::HUD()
{
    elements.push_back(system_info.get());
    elements.push_back(resource_panel.get());
    elements.push_back(timekeeper.get());
    elements.push_back(turn_panel.get());
}

void HUD::update(const sf::Vector2i& mpos)
{
    UI::update(mpos);
}

void HUD::initialize()
{
    system_info = std::make_unique<System_Info>();
    resource_panel = std::make_unique<Resource_Panel>();
    turn_panel = std::make_unique<Panel>(*font);
    timekeeper = std::make_unique<Timekeeper>(*HUD::font, UI::localize);

    system_info->loadFont(font);
    resource_panel->initialize(emptyResource(), *font);
    resource_panel->setPosition(sf::Vector2f(2.f, 2.f));
}

void HUD::loadSystemInfo(Entity e)
{
    if (e == MAX_ENTITIES) {
        system_info->clear();
    }
    else if (system_info->entity != e) {
        system_info->clear();
        auto data = getComponent<Entity_Data>(e);
        auto info = getComponent<Body_Info>(e);
        system_info->addText(data.name, 48);
        std::string classtype;
        if (info.type == "star" || info.type == "system") {
            classtype = info.subtype + "-Class Star";
        }
        else {
            classtype = info.subtype;
        }
        system_info->addText(classtype, 28);

        if (info.type == "system") {
            size_t planet_count = getComponent<Hierarchy>(e).child.size() - 1;
            std::string count = std::to_string(planet_count);
            count += " planet";
            if (planet_count != 1) {
                count += "s";
            }
            system_info->addText(count, 28);
        }
        else if (info.type == "star") {
            // hmmm...
        }

        if (info.owned) {
            auto civilization = getComponent<Entity_Data>(info.owner);
            std::string own = "owned by " + civilization.name;
            system_info->addText(own, 28);
        }

        system_info->addText(data.description, 24);

        auto resource = getComponent<Resource>(e);

        for (auto& r : resource.values) {
            std::string r_text = Resource::toString(r.first);
            std::transform(r_text.begin() + 1, r_text.end(), r_text.begin() + 1, ::tolower);
            r_text += ": ";
            std::stringstream val;
            val << std::fixed << std::setprecision(1) << r.second;
            r_text += val.str();
            system_info->addText(r_text, 24);
        }

        system_info->setText(sf::Vector2f(16.f, 16.f));
    }
}

void HUD::readResources(Entity e)
{
    resource_panel->read(getComponent<Resource>(e));
}

void HUD::enterState()
{}

void HUD::exitState()
{}

void HUD::windowResize(const sf::Vector2u& w_size)
{
    setView(w_size);
    float padding = system_info->getFrame().getOutlineThickness();
    sf::Vector2f si_pos;
    sf::Vector2f si_size;
    si_size.x = 320.f;
    si_size.y = w_size.y - (padding * 2.f) - si_size.x;
    si_pos.x = w_size.x - si_size.x - padding;
    si_pos.y = padding;
    system_info->setPosition(si_pos);
    system_info->setSize(si_size);

    sf::Vector2f tp_size;
    tp_size.x = si_size.x;
    tp_size.y = si_size.x - padding;

    sf::Vector2f tp_pos;
    tp_pos = si_pos;
    tp_pos.y += si_size.y + padding;
    turn_panel->setPosition(tp_pos);
    turn_panel->setSize(tp_size);

    sf::Vector2f tk_pos = si_pos;
    tk_pos.x -= padding;
    tk_pos.x -= timekeeper->getSize().x;

    timekeeper->setPosition(tk_pos);
}

void HUD::updateDate(const Date& date)
{
    timekeeper->setYear(date.year);
    timekeeper->setMonth(date.month);
}

void HUD::updateResourcePanel(const Resource& resource)
{
    resource_panel->read(resource);
}
