# Event
*submodule*
*engine/event/*

[Module Engine](../engine.md)

For publishing and listening to events, through the [Event_Bus](event_bus.md).

Event operations make use of the eponymous struct, which primarily holds two enums:
- **Type**, which refers to an event's... type.
- **Tag**, which serves as a subtype. This is an enum class to differentiate its values from the Type enum.

A default constructor is provided, which accepts Type and Tag variables (the latter defaulting to Tag::NONE)