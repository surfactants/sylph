#include <menu/state/menu_settings_keymapper.hpp>

#include <engine/database/database_commands.hpp>

Menu_Settings_Keymapper::Menu_Settings_Keymapper(std::function<void(std::vector<Command>)> saveCommands)
    : saveCommands { saveCommands }
{
    addNav("save", std::bind(save, this));
    addNav("default", std::bind(loadDefaults, this));
    addNav("cancel", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    sf::Vector2f pos = nav.front().getPosition();
    pos.x += 392.f;
    sf::Vector2f size(900.f, 900.f);
    keymapper.setView(pos, size);
    keymapper.setScrollable(900.f);

    elements.push_back(&keymapper);
}

void Menu_Settings_Keymapper::enterState()
{
    load();
}

void Menu_Settings_Keymapper::exitState()
{
    keymapper.scrollToTop();
}

void Menu_Settings_Keymapper::load()
{
    Database_Commands dbc;
    keymapper.load(dbc.read());
}

void Menu_Settings_Keymapper::loadDefaults()
{
    Database_Commands dbc;
    keymapper.load(dbc.readDefaults());
}

void Menu_Settings_Keymapper::save()
{
    Database_Commands dbc;
    auto data = keymapper.getData();
    dbc.write(data);
    saveCommands(data);
    escape();
}
