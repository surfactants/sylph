# Menu Elements

Menu elements are all derived from the abstract Menu_Element class. Besides functions for most forms of input, it also includes an enumerated State type, as well as an `update()` function which checks the mouse position and sets the state accordingly.

`update()` returns a boolean based on whether or not the mouse is currently over it. State may also be handled out-of-class (see the [Keymapper](keymapper.md) for an example).

A single visual element is provided: `sf::RectangleShape frame`. It must be defined for `contains()` to work.

Menu_Element contains static callbacks to the Menu, allowing an element to set (and unset) itself as the "active" element. They may be invoked by their respective base functions: `activate()` and `deactivate()`. An active element has input priority, and is the only object that receives keyPressed (or textEntered) updates. This behavior may not be desirable - if so, please override Menu::handleInput().

#### State

Following is a list of the states, as well as expected behavior in update().

The basic Sylph menu elements use switch statements to implement state behavior.

- **UNAVAILABLE** update() performs no operations and always returns false
- **READY** if the mouse is inside the element's frame, setState(HIGHLIGHTED) and return true. otherwise, return false.
- **HIGHLIGHTED** if the mouse is outside the element's frame, setState(READY) and return false. otherwise, return true.
- **ACTIVE** there is no default expected behavior for the ACTIVE state in the update() state. Rather, `activate()` should be called on state entry, and deactivation logic should be written somewhere.

### Predefined menu elements:
- [Button](button.md)
- [Check_Box](check_box.md)
- [Color_Selector](color_selector.md)
- [Dropdown](dropdown.md)
- [Keymapper](keymapper.md)
- [Scrollable](scrollable.md)
- [Simple_Textbox](simple_textbox.md)

### Extras
The [Scrollable](scrollable.md) class allows the creation of spatially large classes in small areas, and the means to vertically scroll the view. It is not currently a Menu_Element subclass, though that is a priority, to remove some potential ambiguities. 

### Read more:
- [Menus](../menus.md)