# Component
*concept, enum class*  
*game/component/component.hpp*

## About
All standard components are structs, typically POD (though with no such requirement). They do not inherit anything - the Component type itself is an enum class.

***Please do not use type aliases for components. If multiple components alias the same type, it will crash.***

## Custom Components
- Declare a type T
- Include it in the [component manager](component_manager.md)
- Add an entry to the enum
- Register the component inside Game_State::registration()
- Extend the Component_Serializer (TODO add link):
- - Add a uniquely-named (non-overloading) write function for the type
- - Add entries to the switch statements in **::types()** and **::values()**
- Extend Load_Game (TODO add link):
- - Add a uniquely-named (non-overloading) function which reads values from a save game database and converts them to the type.

---

[Module Game](../game.md)  
[Submodule Core](core.md)  
[Return to Docs](../../docs.md)