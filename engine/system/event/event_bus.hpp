#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include "event.hpp"

using Event_Map = std::unordered_map<Event::Type, std::vector<std::function<void(Event)>>>;

class Event_Bus {
public:
    Event_Bus() = default;

    void listen(Event::Type type, std::function<void(Event)> callback);

    static void publish(Event event);

private:
    static Event_Map listeners;
};

