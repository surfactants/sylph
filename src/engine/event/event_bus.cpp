#include <engine/event/event_bus.hpp>

Event_Map Event_Bus::listeners;

void Event_Bus::listen(Event::Type type, std::function<void(Event)> callback)
{
    listeners[type].push_back(callback);
}

void Event_Bus::publish(Event event)
{
    for (auto& s : listeners[event.type]) {
        s(event);
    }
}
