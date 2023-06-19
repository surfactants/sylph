# Menu_Save_Game
*class : [Menu](menu.md)*  
*ui/menu/menu_save_game.hpp*

## About
Using the encapsulated [Save_List](../elements/save_list.md) object, the player selects a save file which is then overwritten with the current game. A "new" option is also provided, which prompts the player to select a name using a [Dialog](../elements/dialog.md).

## Links

### Save
- Opens a textbox dialog if no save file is selected
- Opens a confirmation dialog for overwrites
- Returns to [Game_State](../../engine/shell/game_state.md)

### Cancel
Returns to the previous menu portal.

---

[Module UI](../ui.md)  
[Submodule Menu](menu.md)  
[Return to Docs](../../docs.md)