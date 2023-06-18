# UI
*module, class*
*ui/ui.hpp*

## About
Sylph's user interface runs on polymorphism, with two inheritance hierarchies: one for state, and one for [elements](elements.md).

State uses the base class UI to store, display, and process input to elements. It contains two different hierarchy paths: one for [Menus](menu/menu.md), and one for the in-game [HUD](hud/hud.md)

TODO
## Public Member Functions

## Protected Member Functions

## Member Objects and Variables

---

## Submodules

### [Elements](elements/elements.md)
Polymorphic element classes

### [Menu](menu/menu.md)
A state group for user navigation and configuration.

### [HUD](hud/hud.md)
A state group for displaying information during gameplay.

---

[Return to docs](../docs.md)
