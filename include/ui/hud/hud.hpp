#pragma once

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

protected:
    static sf::Font* font;

    static System_Info system_info;
    static Resource_Panel resource_panel;
    static Panel turn_panel;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
