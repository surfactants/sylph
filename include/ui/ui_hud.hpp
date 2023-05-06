#pragma once

#include <game/system/system_manager.hpp>

#include "ui.hpp"

class UI_HUD : public UI {
public:
    UI_HUD(System_Manager& systems);

    void loadSystemInfo(Entity e);

    virtual void enterState() override;
    virtual void exitState()  override;

private:
    System_Info system_info;
};
