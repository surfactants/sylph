# Menus

Sylph's menu system comprises a sub-state machine under `Menu_State` (a **Main_State**). It operates like the main state machine: a map containing unique base pointers for each state, and a raw non-owning “current state” pointer.

The **Menu** class itself is an abstract base class base class, defining the bulk of the operations for the menu – particularly input. Individual menu screens are derived from Menu. For more information, please read [Deriving A New Menu State]().

Stored in the base class is a vector of Button objects, called “nav”, which serve to allow user navigation through, to, and away from menu states.

However, Menu only operates on a vector of base Menu_Element pointers, called `elements`. Mouse checks are performed, and input is delegated. Most of the engine’s basic menu elements may be handled totally generically in this manner – any which require special extra handling will be clearly marked in their doc. (Alternately, bring your own special handling.)

## Deriving a new menu state:

It is generally not necessary to override any of the base functions. Only a constructor is required.

Please note: the `elements` vector is not intended to hold raw owning pointers. Derived classes should include storage for elements, whether as single objects or in containers, and then add them to `elements`. Smart pointers are recommended for containers intended to be dynamically updated, to prevent any invalidation of the menu element pointer. In addition, if an element is deleted, call `clearNullElements()`, or face the wrath of the almighty dereferenced nullptr.

### Constructor:
- Initialize the nav by calling `addNav(string title, std::function<void()> target)` for each element.
- a simple pattern for the function is `std::bind(setMenuState, Menu::STATE_NAME)` (or `setMainState`).
- `addNav` has an optional parameter for the nav button’s base state, defaulting to Menu_Element::READY. To prevent a nav button being used until a certain condition is met, pass Menu_Element::UNAVAILABLE. For more information, please view the menu element documentation, linked at the end of this article.
- after all nav elements have been initialized, call `placeNav()`
- call “setEscape”, which provides the menu state’s exit point. It accepts a Menu::State type, along with an overload for Main_State::State.
- - The `escape()` function is called when the user hits the escape key, but it is also a good idea to bind it to a button (or bind it to a function which performs important operations before calling escape)
- The base class contains a variable, `vector<Menu_Element*> elements`. This vector automatically draws the elements, updates them, and delegates input. Support for non-element drawables is a priority, but has not yet been implemented.

### Using a newly-derived menu state:
- add an entry to enum Menu::STATE to refer to the new menu
- include the new menu state’s header in <src/system/main_state/menu_state.cpp>
- construct the menu, adding it to the map. Use the enum entry as the key.
- Define an entry point! The menu is useless unless something can enter it. Add an extra nav button to one of the existing menus, or set up logic somewhere which sets the menu state (and sets the main state to the menu, if necessary).

Input can generally be left alone, though some menus have special requirements, such as Menu_New_Game validating input to set availability of the “start” button, or 

### Examples:
- `Menu_Main`, in `<include/engine/menu/state/menu_main.cpp>`
- `Menu_Settings_Audio`, featuring more elements, custom functions, and even some callbacks. Its implementation file is in the same directory with the same naming convention, but it’s worth having a look at the header, as well as the Menu_State’s implementation, for a complete idea of how it works.
- ‘Menu_New_Game`, featuring many elements.

## Read more...
- [Elements](elements/elements.md)