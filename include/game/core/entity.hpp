#pragma once

#include <bitset>
#include <limits>

#include <game/component/component.hpp>

using Entity = uint_fast16_t;

constexpr static Entity MAX_ENTITIES { 20000 };

constexpr static Entity NULL_ENTITY { std::numeric_limits<Entity>::max() };

using Signature = std::bitset<MAX_COMPONENTS>;
