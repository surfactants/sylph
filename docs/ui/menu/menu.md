# Menu
*submodule, class : [UI](../ui.md)*  
*ui/menu/menu.hpp*

## About
The menus comprise one of the branches of the UI's inheritance tree. State is managed as a substate of the Main_State_Machine, within the [Menu_State](../../engine/shell/menu_state.md).

It is intended for further derivation, with each further element acting as a state. Only nav functionality is added by this class.

There are two types of menua: *Portals* and *Configuration*.

Portals exist to change to other menu states, or exit the program. In addition, they are prepended by a level based on state hierarchy. For example, Menu_Title is a primary portal because its *escape target* (todo inline link) is a different Main_State (todo link). Menu_Settings is a secondary portal because it is accessed from another portal.

Configuration menus provide configuration and other actions.

(TODO consider integrating this classification into code somehow. At the very least add it to doxygen)

## Nav
`nav` is a vector of [Button](../elements/button.md) unique_ptr objects which provide control functionality. In portals, it modifies either menu state or main state. In configuration menus, it typically has a "confirm" button, which performs a task based on secondary element states; less common is a "default" button, which reverts secondary elements to some predetermined set of values; and a "cancel" or "back" button, which reverts values and returns to whichever portal accessed the state.

Two protected, non-virtual helper functions are available for the nav:

### void addNav( *std::string text, std::function<void()> target, Element::State base = Element::READY* )

### void placeNav()
Places the nav buttons. Do this after they've all been added.

## Constants
Several static constants are offered for offsets:
- sf::Vector2f **nav_start**: defaults to (64.f, 64.f)
- unsigned int **nav_csize**: nav character size, default 64
- float **button_offset**: space between buttons, default 32.f
- float **slider_offset**: vertical space between sliders, default 128.f

## States

### [Menu_Title](menu_title.md)
Primary portal accessed on startup (or by the pause menu)

### [Menu_New_Game](menu_new_game.md)
Configuration menu for setting and starting a new game.

### [Menu_Load_Game](menu_load_game.md)
Configuration menu that uses a [Save_List](../elements/save_list.md) to start a game which replicates a save file. Escape state must be set on entry.

### [Menu_Pause](menu_pause.md)
Primary menu portal, accessed from gameplay.

### [Menu_Save_Game](menu_save_game.md)
Configuration menu allowing the player to record the current game state. Uses a [Save_List](../elements/save_list.md) to select a file for overwriting, or to input a new save name.

### [Menu_Settings](menu_settings.md)
Secondary portal for accessing other settings menus. Escape state must be re-set on entry.

### [Menu_Settings_Audio](menu_settings_audio.md)
Configuration providing volume control sliders.

### [Menu_Settings_Game](menu_settings_game.md)
Configuration menu providing game-specific options.

### [Menu_Settings_General](menu_settings_general.md)
Configuration menu for global options, such as language or screen resolution.

### [Menu_Settings_Keymapper](menu_settings_keymapper.md)
Configuration offersling key remapping using the encapsulated [Keymapper](../elements/keymapper.md) object.

## Deriving New Menu States
- Add an entry to UI::State
- Initialize the nav in the constructor by calling `addNav` for each element, then `placeNav`
- `addNav` has an optional parameter for the nav button’s base state, defaulting to Element::READY. To prevent a nav button being used until a certain condition is met, pass Element::UNAVAILABLE.
- call `setEscape()`, which provides an exit point. Accepts UI::State or Main_State::State. Can be updated dynamically; check [Menu_State](../../engine/shell/menu_state.md) for more information.
- Define an entry point by adding an extra nav button to an existing menus, or otherwise set up logic somewhere which sets the menu state (and sets the main state to the menu, if necessary).

---

[Module UI](../ui.md)  
[Return to Docs](../../docs.md)
