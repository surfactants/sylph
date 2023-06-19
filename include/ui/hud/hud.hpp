#pragma once

#include <game/core/ecs_core.hpp>

#include <ui/ui.hpp>

#include <ui/elements/system_info.hpp>

class HUD : public UI {
public:
    HUD();

    static void initialize(ECS_Core* x_core);

    static void loadSystemInfo(Entity e);

    virtual void update(const sf::Vector2i& mpos) override;

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

    static std::function<void(UI::State)> setHUDState;

protected:
    static ECS_Core* core;

    static System_Info system_info;

    static sf::Font* font;
};
