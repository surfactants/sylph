#pragma once

#include <ui/ui.hpp>

class Menu : public UI {
public:
    Menu();

    void addNav(std::string text, std::function<void()> target, Element::State base = Element::READY);
    void placeNav();

    virtual void windowResize(const sf::Vector2u& w_size);

protected:
    std::vector<std::unique_ptr<Button>> nav;

    const static sf::Vector2f nav_start;
    constexpr static unsigned int nav_csize { 64 };
    constexpr static float button_offset { 32.f };
    constexpr static float slider_offset { 128.f };
};
