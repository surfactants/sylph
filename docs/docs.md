# Documentation

## About
Sylph is intended as a flexible, extensible, and lightweight game engine, written in and for C++/SFML. It consists of four modules\*, which further consist of submodules. Submodules range from simple utility libraries to complex systems.

*\*the term "module" is organizational, and therefore not to be confused with the homonymous C++20 feature*

## Modules

### [Engine](engine/engine.md)
Forms the core of Sylph's functionality, with main state, audio, input, events, etc.

### [Game](game/game.md)
The substate machine and Entity-Component-System which comprise gameplay.

### [UI](ui/ui.md)
User interfaces for menus and in-game HUD.

#### See also

- [Style](notes/style.md)