# Panel
*class : [Element](element.md)*  
*ui/elements/panel.hpp*

## About
The panel is a versatile element which serves as a container for other elements, to which it delegates input using the same strategy as the menu system.

In addition, it can contain plain sf::Text or sf::Sprite elements.

All contained renderables are passed and stored as pointers. In addition, an enumerated Place type is used to determine how the element is positioned (LEFT, CENTER, RIGHT).

Multiple panels can be bundled into a **[Tabbed_Panel](tabbed_panel.md)** structure.

Derivation is encouraged for specific UI panels which control the management of their own elements.

For example, the 4x prototype's new game menu contains several Panel objects, such as the *Home_Panel*:

```
	class Home_Panel : public Panel {
		// ...

		std::shared_ptr<[Simple_Textbox](simple_textbox.md)> homeworld_name { nullptr };

		std::shared_ptr<[Simple_Textbox](simple_textbox.md)> homeworld_name { nullptr };

		std::shared_ptr<[Dropdown](dropdown.md)<std::string>> homeworld_name { nullptr };

		std::shared_ptr<sf::Text> title { nullptr };
	};
```

The constructor then defines each object and uses the **addElement** and **addText** methods.

The use of std::shared_ptr is encouraged, and is required if the panel is part of a Tabbed_Panel.

## Important Notes
A public sf::View pointer must be assigned. It's used to allow functionality with elements that define their own views.

---

[Module UI](../ui.md)  
[Submodule Elements](elements.md)  
[Return to Docs](../../docs.md)