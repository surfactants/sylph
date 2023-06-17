# Menu_New_Game
*class : [Menu](menu.md)*
*ui/menu/menu_new_game.hpp*

## About
Here is where the player selects options which will be used to create a new game.

An additional protected method is provided:

### bool validate()
Checks all pertinent elements to determine availability of the "start" button.

**handleInput()** is overridden to call this.

## Links

### Start
Only available if input has passed validation. Initiates game generation with a transition to [Game_State](../../engine/shell/game_state.md).

### Cancel
Returns to the previous menu portal.

---

[Module UI](../ui.md)
[Submodule Menu](menu.md)
[Return to Docs](../../docs.md)