# Menu Elements

Menu elements are all derived from the abstract Menu_Element class.

Sylph provides several useful elements:
- [Button](button.md)
- [Check_Box](check_box.md)
- [Color_Selector](color_selector.md)
- [Dropdown](dropdown.md)
- [Keymapper](keymapper.md)
- [Scrollable](scrollable.md)
- [Simple_Textbox](simple_textbox.md)

# State
Following is a list of the states, as well as expected behavior in update().

The basic Sylph menu elements use switch statements to implement state behavior.

- **UNAVAILABLE** update() performs no operations and always returns false
- **READY** if the mouse is inside the element's frame, setState(HIGHLIGHTED) and return true. otherwise, return false.
- **HIGHLIGHTED** if the mouse is outside the element's frame, setState(READY) and return false. otherwise, return true.
- **ACTIVE** there is no default expected behavior for the ACTIVE state in the update() state. Rather, `activate()` should be called on state entry, and deactivation logic should be written somewhere.

# Member variables

## Public

### set_active

Callback which registers `this` with the active menu

---

### set_inactive

---
Callback which de-registers `this` from the active menu (if registered)

---
## Protected

### sf::RectangleShape frame

The sole visual element provided by the base class. This should be defined, as `contains()` relies on it.

---
### State state

---
### State base_state
Generally passed to an object's constructor as an optional parameter (defaulting to READY). setState() should be called with the passed base state.

---

# Public functions:

Most functions are virtual.

---
### virtual bool update(const sf::Vector2i& mouse_pos)
A pure virtual function. The typical implementation is as follows:
- check and store if the element contains the mouse pos
- switch (state), update from contains
- return contains

---
### virtual void clickLeft()
Left mouse press. Pure.

---
### virtual void releaseLeft()
Left mouse release. Pure.

---
### virtual void clickRight()
Not pure.

---
### virtual void releaseRight()
Not pure.

---
### virtual void textEntered(const sf::Event& event)
Only triggers for the active element. Not pure.

---
### virtual void keyPressed(sf::Keyboard::Key)
Only triggers for the active element. Not pure.

---
### virtual void scroll(float delta)
Only triggers for the highlighted element. Not pure.
### virtual void activate()
Invokes the set_active callback, registering `this` with the active menu. The base version should be called when overridden.

---
### void deactivate()
Invokes the set_inactive callback, de-registering `this` from the active menu. The base version should be called when overridden.

---
### virtual void setState(State state)
This is typically overridden to reflect visual changes or call activate() and deactivate().

---
### bool available() const
returns (state != UNAVAILABLE)

---
### bool highlighted() const
returns (state == HIGHLIGHTED)

---
### bool active() const
returns (state == ACTIVE)

---
### bool contains(const sf::Vector2<T>& v) const
returns (frame.contains(v))
 
---
### void setToBase()
resets `state` to `base_state`
  
---

## Extras
The [Scrollable](scrollable.md) class allows the creation of spatially large classes in small areas, and the means to vertically scroll the view. It is not currently a Menu_Element subclass, though that is a priority, to remove some potential ambiguities. 

## Read more:
- [Menus](../menu.md)