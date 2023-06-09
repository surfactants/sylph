# Component
*game/component/component.hpp*

Components are structs, typically POD (though with no such requirement). They do not inherit anything - the Component type is an enum class. Sylph provides several standard component types, but more are easily added:
- Declare a struct, T
- Add an entry to the enum
- Register the component inside Game_State::registration()
- Extend the Component_Serializer (TODO add link):
- - Add a uniquely-named (non-overloading) write function for the type
- - Add entries to the switch statements in **::types()** and **::values()**
- Extend Load_Game (TODO add link):
- - Add a uniquely-named (non-overloading) function which reads values from a save game database and converts them to the type.