# Double_Click
*class*
*engine/input/double_click.hpp*

[Module Engine](../engine.md)
[Submodule Input](input.md)

Uses an sf::Clock object to determine time intervals between mouse clicks.

## Public Member Function
- bool **operator () ():** checks the time since the last mouse press. returns true if it is lower than the threshold. Restarts the timer.