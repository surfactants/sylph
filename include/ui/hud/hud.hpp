#pragma once

#include <game/core/ecs_core.hpp>

#include <ui/ui.hpp>


class HUD : public UI {
public:
    HUD();

    virtual void update(const sf::Vector2i& mpos) override;

    virtual void windowResize(const sf::Vector2u& w_size) override;

    static std::function<void(UI::State)> setHUDState;

    template <typename T>
    static inline std::function<T(Entity)> getComponent;

protected:
    static sf::Font* font;
};
