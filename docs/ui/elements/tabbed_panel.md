# Tabbed_Panel
*class : [Element](element.md)*  
*ui/elements/panel.hpp*

## About
Provides a means of switching between multiple [Panel](panel.md) objects, and displaying/accepting input to one at a time.

## Example
The 4x prototype's new game menu contains several different panels for various starting options:

```
	std::unique_ptr<Tabbed_Panel> panels { nullptr };

	std::shared_ptr<Species_Panel> species { nullptr };
	std::shared_ptr<Home_Panel> home { nullptr };
	std::shared_ptr<Civ_Panel> civ { nullptr };
```

In the constructor, they're defined and added to the tabbed structure.
```
    const sf::Vector2f tab_size(96.f, 870.f); // controls the size of the tab control panel
    const sf::Vector2f panel_size(1300.f, tab_size.y);

    const sf::Vector2f tab_pos = nav.front()->getPosition() + sf::Vector2f(392.f, 0.f);
    const sf::Vector2f panel_pos = tab_pos + sf::Vector2f(tab_size.x, 0.f);
    
    panels = std::make_unique<Tabbed_Panel>();
    panels->setPosition(tab_pos);
    panels->setSize(tab_size);

    species = std::make_shared<Species_Panel>(*font, panel_pos, panel_size, localize);
    species->view = &view;
    home = std::make_shared<Home_Panel>(*font, panel_pos, panel_size, localize);
    home->view = &view;
    civ = std::make_shared<Civ_Panel>(*font, panel_pos, panel_size, localize);
    civ->view = &view;

    // SAVE PANELS
    panels->addPanel(species);
    panels->addPanel(home);
    panels->addPanel(civ);

    elements.push_back(panels.get());
```

---

[Module UI](../ui.md)  
[Submodule Elements](elements.md)  
[Return to Docs](../../docs.md)