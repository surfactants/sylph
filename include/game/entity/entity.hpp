#pragma once

#include <bitset>

#include <game/component/component.hpp>

using Entity = uint_fast16_t;

constexpr static Entity MAX_ENTITIES { 10000 };

using Signature = std::bitset<MAX_COMPONENTS>;
