# Core
*submodule*  
*game/core/*

## About
Sylph uses an Entity Component System to provide extensible game behavior, based on [Austin Morlan's implementation](https://austinmorlan.com/posts/entity_component_system/) (and currently borrowing some code from it)

Each part is handled by a manager class, all held by a wrapper class (ECS_Core), which itself is stored as a static unique pointer in the base Game class.
- [Entity_Manager](entity_manager.md): functions out-of-the-box, no additions required
- [Component_Manager](component_manager.md): requires registration of each component type
- [System_Manager](system_manager.md): this is where most of the game's functionality should occur.

---

[Module Game](../game.md)  
[Return to Docs](../../docs.md)