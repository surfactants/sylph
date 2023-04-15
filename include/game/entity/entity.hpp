#pragma once

#include <bitset>

#include "component.hpp"

using Entity = uint_fast16_t;

using Signature = std::bitset<static_cast<uint8_t>(Component::SIZE)>;
