# Input_Package
*class*  
*engine/input/input_package.hpp*

## About
Stores functions bound to specific mouse or keyboard input, in public maps. Also provides invocation functions.

## Public Member Functions
Each of these functions has an overload for both *sf::Keyboard::Key* and *sf::Mouse::Button* parameters.

### void addPress( *key or button, std::function<void()> func* )
stores the passed function in a map keyed to the passed enumerated input. Invoked when *press()* is called with that input.

### void addRelease( *key or button, std::function<void()> func* ):
same as *addPress()*, but invoked when *release()* is called.

### void press( *key or button* )
to be called on ::KeyPressed or ::MouseButtonPressed events.

### void release( *key or button* )
to be called on ::KeyReleased or ::MouseButtonReleased events.

## Mousewheel Scrolling
Because there is only one such event, a public std::function<void(float)> called *scroll* is offered.

---

[Module Engine](../engine.md)  
[Submodule Input](input.md)  
[Return to docs](../../docs.md)