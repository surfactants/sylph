#pragma once

#include <engine/util/interface_element.hpp>

class UI_Element : public Interface_Element {
public:
    virtual bool update(const sf::Vector2i& mpos) = 0;
    virtual void clickLeft() = 0;
    virtual void releaseLeft() = 0;

    inline static std::function<void(UI_Element*)> setActive = [](UI_Element*) {};
    inline static std::function<void(UI_Element*)> setInactive = [](UI_Element*) {};

    virtual void deactivate() override
    {
        setInactive(this);
        setToBase();
    }

    virtual void activate() override
    {
        setActive(this);
    }
};
