# Context
*class*  
*game/system/context.hpp*

Provides a state machine for System_Manager through the encapsulated enum, **Type**. Also stores a pointer to the currently active sf::View object. View the prototype for an example, where it is used to switch between "galaxy" and "solar system" contexts.

## Public Member Functions:
- Type **operator() ( ):** returns the current enumerated type value
- void **toggle():** For cycling context changes
- void **set( *Type c, Entity e* ):**
- void **resetView( *Type t* ):**
- void **setView( *const sf::Vector2u w_size* ):** reinitializes the current view to fill the passed size; currently only functions with views that fill the whole screen

---

[Module Game](../../game.md)  
[Submodule Core](../core.md)  
[Return to Docs](../../../docs.md)