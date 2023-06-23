# Documentation

## About
Sylph is intended as a flexible, extensible, and lightweight game engine, written in and for C++/SFML.

## Structure
Sylph consists of three *modules*, themselves further comprised of *submodules*. Submodules range from simple utility libraries to complex systems.

Header and implementation files are split into the *include/* and *src/* directories, respectively. Both are further organized into *module_name/submodule_name* directories. For example, to access the Engine module's Input submodule header file, one would go to the *engine/input* directory.

The documentation's file structure also follows this pattern.

## Modules

### [Engine](engine/engine.md)
Forms the core of Sylph's functionality, with main state, audio, input, events, etc.

### [Game](game/game.md)
The substate machine and Entity-Component-System which comprise gameplay.

### [UI](ui/ui.md)
User interfaces for menus and in-game HUD.

#### See also

- [Style](notes/style.md)