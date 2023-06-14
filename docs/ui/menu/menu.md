# Menu
*submodule, class : [UI](../ui.md)*
*ui/menu/menu.hpp*

## About
The menus comprise one of the branches of the UI's inheritance tree. State is managed as a substate of the Main_State_Machine, within the [Menu_State](../../engine/system/menu_state.md).

It is intended for further derivation, with each further element acting as a state. Only nav functionality is added by this class.

## Nav
`nav` is a vector of Button unique_ptr objects which modifies state, between either menu states or main states. Two protected, non-virtual helper functions are available:

### void addNav( *std::string text, std::function<void()> target, Element::State base = Element::READY* )

### void placeNav()
Places the nav buttons 

## Constants
Several static constants are offered for offsets:
- sf::Vector2f **nav_start**: defaults to (64.f, 64.f)
- unsigned int **nav_csize**: nav character size, default 64
- float **button_offset**: space between buttons, default 32.f
- float **slider_offset**: vertical space between sliders, default 128.f

## States

### [Menu_Title](menu_title.md)

### [Menu_New_Game](menu_new_game.md)

### [Menu_Load_Game](menu_load_game.md)

### [Menu_Pause](menu_pause.md)

### [Menu_Save_Game](menu_save_game.md)

### [Menu_Settings](menu_settings.md)

### [Menu_Settings_Audio](menu_settings_audio.md)

### [Menu_Settings_Game](menu_settings_game.md)

### [Menu_Settings_General](menu_settings_general.md)

### [Menu_Settings_Keymapper](menu_settings_keymapper.md)

## Deriving New Menu States
- Add an entry to UI::State
- Initialize the nav in the constructor by calling `addNav` for each element, then `placeNav`
- `addNav` has an optional parameter for the nav button’s base state, defaulting to Element::READY. To prevent a nav button being used until a certain condition is met, pass Element::UNAVAILABLE.
- call `setEscape()`, which provides an exit point. Accepts UI::State or Main_State::State. Can be updated dynamically; check [Menu_State](../../engine/system/menu_state.md) for more information.
- Define an entry point by adding an extra nav button to an existing menus, or otherwise set up logic somewhere which sets the menu state (and sets the main state to the menu, if necessary).

---

[Module UI](../ui.md)
[Return to Docs](../../docs.md)