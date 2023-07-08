#include <ui/hud/hud_simulate.hpp>

HUD_Simulate::HUD_Simulate()
{
    std::string text = "SIMULATING";
    std::string loc = localize(text);
    panel_text.setString(loc);
    localize.recordPersistent(text, &panel_text);

    panel_text.setFillColor(Palette::white);
    panel_text.setFont(*font);
}

void HUD_Simulate::enterState()
{
    clock.restart();

    turn_panel->addText(&panel_text, Panel::CENTER, turn_panel->getSize().x);
}

void HUD_Simulate::exitState()
{
    turn_panel->clear();
}
