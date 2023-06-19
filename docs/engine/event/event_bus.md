# Event_Bus
*class*  
*engine/event/event_bus.hpp*

## About
Accepts the creation of Event objects statically, and then propagates those events to any functions that have been registered as listeners.

## Public Member Functions
### void listen( *Event::Type type, std::function<void(Event)> callback* )
registers a function to be called whenever an Event with the passed type is generated.

### static void publish( *Event event* )
Propagates an event to all appropriate listeners.


---

[Module Engine](../engine.md)  
[Submodule Event](event.md)  
[Return to docs](../../docs.md)
