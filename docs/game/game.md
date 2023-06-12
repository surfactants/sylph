# Game
*module*

[Return to docs](../docs.md)

The game is handled through a sub-state machine in the Main_State_Machine's Game_State. (TODO add links). Like the main state, the substate machine is polymorphic, deriving from the abstract *Game* class.

An [Entity Component System](core/ecs.md) forms the basis of game behavior. The pertinent manager classes are static, providing persistence of game data across states.

See also the submodule for [world generation](world/world_generation.md)