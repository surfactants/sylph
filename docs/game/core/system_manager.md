* System_Manager
*game/core/system_manager.hpp*

The system manager is where all game logic is performed, through the encapsulated [systems](system.md).

In addition to a default parameterless constructor, it has two public member functions:
- void **update( *const float delta_time* ):**
- void **windowResize( *const sf::Vector2u& window_size* ):**

... as well as a template std::function object for getting components (getComponent) (TODO figure something out with the static System callable. this replication is unneeded)

Polymorphic access to the systems is provided by the **map** member (*std::map<std::string, System*>). Please keep in mind that systems have no virtual functions; without downcasting, the utility is limited to accessing the entities and the name.

All members are publicly accessible.

There are a few important classes included by default:
- **[Context](system/context.md):** Provides a state machine
- **[Input_Accelerator](system/input_accelerator.md):** Accepts WASD-style input and calculates a movement vector.
- **[Renderer](system/renderer.md):** Draws game objects in layers and provides view handling