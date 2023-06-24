#include <ui/hud/hud_simulate.hpp>

HUD_Simulate::HUD_Simulate()
{}

void HUD_Simulate::enterState()
{
    clock.restart();

    std::string text = "SIMULATING";
    std::string loc = localize(text);
    turn_panel->setString(loc);
    localize.recordPersistent(text, &turn_panel->getText());
}

void HUD_Simulate::exitState()
{
    localize.erase(&turn_panel->getText());
}
