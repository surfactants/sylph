#include <menu/state/menu_settings_keymapper.hpp>

#include <system/database/database_commands.hpp>

Menu_Settings_Keymapper::Menu_Settings_Keymapper(std::function<std::vector<Command>()> loadCommands
                                               , std::function<void(std::vector<Command>)> saveCommands)
    : loadCommands { loadCommands }
    , saveCommands { saveCommands }
{
    nav.push_back(Button(std::string("save"), *font, std::bind(save, this), csize));
    nav.push_back(Button(std::string("default"), *font, std::bind(setMenuState, Menu::SETTINGS), csize));
    nav.push_back(Button(std::string("cancel"), *font, std::bind(&Menu::escape, this), csize));

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
    Menu::enterState();
    keymapper.load(loadCommands(), *font);
}

void Menu_Settings_Keymapper::exitState()
{
    Menu::exitState();
    keymapper.reset();
}

void Menu_Settings_Keymapper::save()
{
    Database_Commands dbc;
    dbc.write(keymapper.getCommands());
    saveCommands(keymapper.getCommands());
    escape();
}
