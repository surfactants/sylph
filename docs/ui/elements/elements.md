# Elements
*submodule*  
*ui/elements/*

## About
UI Elements are handled polymorphically, through the abstract [Element](element.md) class.

## Basic Elements
- [Button](button.md)
- [Check_Box](check_box.md)
- [Color_Selector](color_selector.md)
- [Info_Panel](info_panel.md)
- [Simple_Textbox](simple_textbox.md)
- [Slider](slider.md)

In addition, several *compound elements* are provided, which are comprised of many sub-elements:
## Compound Elements
- [Dialog](dialog.md)
- [Dropdown](dropdown.md)
- [Keymapper](keymapper.md)
- [Save_List](save_list.md)
- [Toggle_Scroller](toggle_scroller.md)

Finally, a utility class for vertical scrolling is available:
### [Scrollable](scrollable.md)
Contains an sf::Viewport object which can be moved with mousewheel input.

---

[Module UI](../ui.md)  
[Return to Docs](../../docs.md)