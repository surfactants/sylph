# Element
*class*
*ui/elements/element.hpp*

## About
Base UI element class

## State
State is an enum with the following entries:
- **UNAVAILABLE** update() performs no operations and returns false
- **READY** if the mouse is inside the element's frame, setState(HIGHLIGHTED) and return true. otherwise, return false.
- **HIGHLIGHTED** if the mouse is outside the element's frame, setState(READY) and return false. otherwise, return true.
- **ACTIVE** there is no default expected behavior for the ACTIVE state in the update() state. Rather, `activate()` should be called on state entry, and deactivation logic should be written somewhere. Receives priority input.
- **SELECTED** todo. Keyboard control selection. Like Active, receives priority input.

Default elements use switch statements to implement state behavior.

## Public Member Functions
Most functions are virtual. Some are unimplemented, so as to be optional.

### virtual void setPosition( *const sf::Vector2f& position* )

### virtual void setState( *State state* )
Overrides must modify the state variable.

### const sf::RectangleShape& getFrame() const

### bool contains ( *const sf::Vector2<T> v* ) const

### bool available() const
True if state is AVAILABLE

### bool highlighted() const
True if state is HIGHLIGHTED

### bool active() const
True if state is ACTIVE

### bool selected() const
True if state is SELECTED

### virtual void activate()
Invokes the setActive callback, registering `this` as the active UI element. Overrides must either call the base version or invoke setActive manually.

### virtual void deactivate()
Invokes the unsetActive callback, unregistering `this` as the active UI element. Overrides must either call the base version or invoke setActive manually.

### virtual void select()

### virtual void deselect()

### virtual void update( *const sf::Vector2i& mpos* )
*Pure*

### void clickLeft()
*Pure*

### void releaseLeft()
*Pure*

### virtual void clickRight()
*Unimplemented*

### virtual void releaseRight()
*Unimplemented*

### virtual void textEntered( *const sf::Event& event* )
*Unimplemented*

### virtual void keyPressed( *sf::Keyboard::Key key* )
*Unimplemented*

### virtual void scroll( *float delta* )
*Unimplemented*

## Public Member Variables

### *static* std::function<void(Element*)> setActive
Callback which registers `this` as the active UI element

### *static* std::function<void(Element*)> unsetActive
Callback which de-registers `this` as the active UI element

### *static* std::function<void(Element*)> setSelected
Callback which registers `this` as the selected UI element

### *static* std::function<void(Element*)> unsetSelected

## Protected Member Variables

### sf::RectangleShape frame
The sole visual element provided by the base class. This should be defined, as `contains()` relies on it.

TODO: change to RoundedRectangle...

### State state
Current enumerated state value

### State base_state
Generally passed to an object's constructor as an optional parameter (defaulting to READY). setState() should be called with the passed base state.

---

[Module UI](../ui.md)
[Submodule Elements](elements.md)
[Return to Docs](../../docs.md)