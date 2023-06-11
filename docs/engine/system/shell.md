# Shell
*class*
*engine/system/shell.hpp*

The outermost abstraction layer. Provides highest level logic and encapsulates every other class, with direct encapsulation of the following:
- window (sf::RenderWindow)
- [Event_Bus](../event/event_bus.md)
- [Audio](../audio/audio.md)
- [Main_State_Machine](main_state_machine.md)

The only non-constructor public member function is **run()**, which starts the main window loop.