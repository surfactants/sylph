# Component_Manager
*game/core/component_manager.hpp*

Handles the creation, destruction, and storage of [Component](component.md) types.

Public member functions:
- std::function<T(Entity)> **registerComponent()**: this template function must be called for each and every component - ***but by default, this is handled by the similar Game_State::registerComponent<T>***, which passes the returned function (**getComponent<T>**) where it is needed. The Game_State functions are called from its member function, **::registration()**.
- Component_Type
