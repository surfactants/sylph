# Component_Manager
*class*
*game/core/component_manager.hpp*

Handles the creation, destruction, and storage of [Component](component.md) types.

## Public Member Functions

### std::function<T(Entity)> registerComponent()
this template function must be called for each and every component - ***but by default, this is handled by the similar Game_State::registerComponent<T>***, which passes the returned function (**getComponent<T>**) where it is needed. This is handled in [Game_State](../../engine/shell/game_state.md)

---

[Module Game](../game.md)
[Submodule Core](core.md)
[Return to Docs](../../docs.md)
