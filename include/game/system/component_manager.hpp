#pragma once

#include "component_library.hpp"

class Component_Manager {
public:
    Component_Manager();
    void clear();

private:
    Component_Library library;
};
