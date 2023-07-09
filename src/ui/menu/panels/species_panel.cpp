#include <ui/menu/panels/species_panel.hpp>

Species_Panel::Species_Panel(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, Localizer& localize)
    : Panel(pos, size)
{
    // title
    std::string text = "SPECIES_TITLE";
    std::string loc = localize(text);
    title = std::make_shared<sf::Text>(loc, font, title_csize);
    localize.recordPersistent(text, title.get());
    addText(title.get(), Panel::LEFT, size.x);

    const sf::Vector2f textbox_size(512.f, 96.f);

    // elements
    name = std::make_shared<Simple_Textbox>("SPECIES_NAME", font, elem_csize);
    name->setSize(textbox_size);
    addElement(name.get(), Panel::LEFT);

    const sf::Vector2f box_size(512.f, 512.f);

    std::vector<std::pair<std::string, std::string>> drop_data = {
        { "carbon", "CARBON" },
        { "silicon", "SILICON" },
        { "gaseous", "GASEOUS" }
    };

    biochemistry = std::make_shared<Dropdown<std::string>>();
    biochemistry->setView(sf::Vector2f(0.f, 0.f), box_size, sf::Vector2u(1920, 1080));
    biochemistry->load(drop_data, font, elem_csize, 0);
    addElement(biochemistry.get(), Panel::RIGHT);

    drop_data = {
        { "water", "WATER" },
        { "ammonia", "AMMONIA" },
        { "methane", "METHANE" },
        { "fluorane", "FLUORANE" }
    };

    solvent = std::make_shared<Dropdown<std::string>>();
    solvent->setView(sf::Vector2f(0.f, 0.f), box_size, sf::Vector2u(1920, 1080));
    solvent->load(drop_data, font, elem_csize, 0);
    addElement(solvent.get(), Panel::RIGHT);

    temperature = std::make_shared<Slider>("TEMPERATURE_PREFERENCE", elem_csize);
    temperature->set(sf::Vector2f(0.f, 0.f), font);
    addElement(temperature.get(), Panel::RIGHT);
}

void Species_Panel::reset()
{
    name->clear();
    biochemistry->set(0u);
    solvent->set(0u);
}
