# Entity
*concept, unsigned integral type alias*
*game/core/entity.hpp*

This file contains the following definitions:
- **Entity**, an alias for uint_fast16_t
- **MAX_ENTITIES**, a compile-time constant defining the maximum number of allowable entities.
- **Signature**, an alias for a bitset sized to the number of component types. The signature records which component types are owned by an entity.
