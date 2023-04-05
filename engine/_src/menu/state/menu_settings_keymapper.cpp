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
    sf::Vector2f size(392.f, 900.f);
    keymapper.setView(pos, size);
    keymapper.setScrollable(900.f);
}

void Menu_Settings_Keymapper::update(const sf::Vector2i& mpos)
{
    Menu::update(mpos);

    keymapper.update(mpos);
}

void Menu_Settings_Keymapper::enterState()
{
    keymapper.load(loadCommands(), *font, csize);
}

void Menu_Settings_Keymapper::exitState()
{}

void Menu_Settings_Keymapper::save()
{
    Database_Commands dbc;
    dbc.write(keymapper.getCommands());
    saveCommands(keymapper.getCommands());
    escape();
}

void Menu_Settings_Keymapper::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& n : nav) {
        target.draw(n, states);
    }
    for (const auto& slider : sliders) {
        target.draw(slider, states);
    }
    target.draw(keymapper, states);
}
