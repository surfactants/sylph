#pragma once

#include "system.hpp"

class Civilizations : public System {
public:
    Civilizations();
    void add(Entity e)
    {
        entities.insert(e);
    }
};
