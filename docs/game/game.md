# Game
*module, class*

## About
The game is handled through a sub-state machine in the Main_State_Machine's Game_State. (TODO add links). Like the main state, the substate machine is polymorphic, deriving from the abstract *Game* class.

Internal behavior follows Entity-Component-System architecture. The pertinent manager classes are encapsulated within a static data structure, providing persistence of game data across states, as well as simple access from other modules.

## Submodules

### [Core](core/core.md)
Contains the Entity-Component-System classes

### [World Generation](world/world_generation.md)

---

[Return to Docs](../docs.md)