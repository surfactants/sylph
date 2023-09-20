# Component
*concept, enum class*  
*game/component/component.hpp*

## About
All standard components are structs, typically POD (though with no such requirement). They do not inherit anything - the Component type itself is an enum class.

***The use of type aliases as components is discouraged. Please keep in mind that if two components alias the same type, the program will crash.***

## Custom Components
- Declare a type T
- Include it in <[game](../game.md)/[core](core.md)/components.hpp>
- Add an entry to the enum
- Register the component inside <[engine](../../engine/engine.md)/[shell](../../engine/shell.md)/game_state>::registration()
- Extend the Component_Serializer (<[game](../game.md)/[core](core.md)/[component_serializer](component_serializer.md)>) with a uniquely-named (non-overloading) write function for the type
- - Add entries to the switch statements in **::types()** and **::values()**
- Extend Load_Game (<[game](../game.md)/[core](core.md)/[load_game](load_game.md)>) with a uniquely-named (non-overloading) function which reads values from a save game database and converts them to the type.

---

[Module Game](../game.md)  
[Submodule Core](core.md)  
[Return to Docs](../../docs.md)