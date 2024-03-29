#include <ui/menu/menu_settings_keymapper.hpp>

#include <engine/database/database_commands.hpp>

Menu_Settings_Keymapper::Menu_Settings_Keymapper(std::function<void(std::vector<Command>)> saveCommands)
    : saveCommands { saveCommands }
{
    addNav("BUTTON_SAVE", std::bind(save, this));
    addNav("BUTTON_DEFAULT", std::bind(loadDefaults, this));
    addNav("BUTTON_CANCEL", std::bind(escape, this));

    setEscape(Menu::SETTINGS);

    placeNav();

    sf::Vector2f pos = nav.front()->getPosition();
    pos.x += 392.f;
    sf::Vector2f size(900.f, 900.f);
    keymapper.setView(pos, size);
    keymapper.setScrollable(size.y);

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
