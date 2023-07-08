#pragma once

#include <game/component/date.hpp>

#include <game/core/ecs_core.hpp>

#include <ui/ui.hpp>

#include <ui/elements/system_info.hpp>

class HUD : public UI {
public:
    HUD();

    static void initialize();

    static void loadSystemInfo(Entity e);
    static void readResources(Entity e);

    virtual void update(const sf::Vector2i& mpos) override;

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

    static std::function<void(UI::State)> setHUDState;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

    void updateDate(const Date& date);
    void updateResourcePanel(const Resource& resource);

protected:
    static sf::Font* font;

    static std::unique_ptr<System_Info> system_info;
    static std::unique_ptr<Resource_Panel> resource_panel;
    static std::unique_ptr<Panel> turn_panel;
    static std::unique_ptr<Timekeeper> timekeeper;

    sf::Text panel_text;
};
