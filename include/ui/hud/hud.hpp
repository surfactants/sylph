#pragma once

#include <game/core/ecs_core.hpp>

#include <ui/ui.hpp>

#include <ui/elements/system_info.hpp>

class HUD : public UI {
public:
    HUD(ECS_Core& core);

    void loadSystemInfo(Entity e);

    virtual void enterState() override;
    virtual void exitState() override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

protected:
    ECS_Core& core;

    System_Info system_info;

    static sf::Font* font;
};
