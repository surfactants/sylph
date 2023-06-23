# Game_State
*class : [Main_State](main_state.md)*  
*engine/shell/game_state.hpp*

## About
Delegates to the [Game](../../game/game.md) and [HUD](../../ui/hud/hud.md).


## Input
Game_State parses input through two [Input_Package](../input/input_package.md) objects. The first, simply called `input`, is inactive if the UI detects input. The second, `priority_input`, parses input no matter what.

The input packages are assigned through `::loadCommands` (which themselves are loaded by Database_Commands). These are connected via the `string_to_function` map, keyed to a unique string identifier for each function, and containing Function structs, which store a std::function<void()> object, as well as a `priority` boolean. Connection occurs in `::loadFunctions()`.

---

[Module Engine](../engine.md)  
[Submodule Shell](shell.md)  
[Return to docs](../../docs.md)