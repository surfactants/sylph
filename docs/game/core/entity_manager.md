# Entity_Manager
*class*  
*game/core/entity_manager.hpp*

## About
Handles the creation, destruction, and storage of [Entity](entity.md) objects along with their signatures.

## Public Member Functions
- **Entity_Manager()**: the default (and only) constructor fills the available entity queue based on the MAX_ENTITIES value defined in core/entities.hpp
- Entity **create()**: returns the next available Entity
- void **destroy(Entity e)**: clears the signature of the passed entity, and re-adds it to the available queue	
- void **define(Entity e, Signature s)**: records the provided entity's bitset signature
- Signature **signature(Entity e)**: returns the provided entity's bitset signature

---

[Module Game](../game.md)  
[Submodule Core](core.md)  
[Return to Docs](../../docs.md)