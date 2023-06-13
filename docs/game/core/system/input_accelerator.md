# Input_Accelerator
*class*
*game/system/input_accelerator.hpp*

Accepts WASD-style input and calculates a movement vector. Despite residing in the *system/* directory, and being encapsulated by System_Manager, this class does not derive from System.

## Example
In the prototype, the Accelerator is used to provide RTS-style camera movement.

In *game/core/system_manager.cpp*, the vector is calculated and moved:
```
	sf::Vector2f v = accelerator.update(delta_time);
	camera_controller.update(v, mpos);
```

And in *engine/system/game_state.cpp*, those functions are hooked up to the appropriate input (TODO link to input package)
```
void Game_State::loadFunctions()
{
    // here, bind game functions to string identifiers

    auto acc = &Game::core->systems.accelerator;
    string_to_function = {
        // movement functions
        { "move up",    std::bind(&Input_Accelerator::startUp,      acc) },
        { "stop up",    std::bind(&Input_Accelerator::stopUp,       acc) },
        { "move left",  std::bind(&Input_Accelerator::startLeft,    acc) },
        { "stop left",  std::bind(&Input_Accelerator::stopLeft,     acc) },
        { "move down",  std::bind(&Input_Accelerator::startDown,    acc) },
        { "stop down",  std::bind(&Input_Accelerator::stopDown,     acc) },
        { "move right", std::bind(&Input_Accelerator::startRight,   acc) },
        { "stop right", std::bind(&Input_Accelerator::stopRight,    acc) },

        // ...
    };
}
```

## Public Member Functions
- explicitly defaulted constructor
- sf::Vector2f **update( *const float delta_time* ):** calculates and returns the framewise velocity
- void **setMaxSpeed( *float speed* )
- void **setAcceleration( *float acceleration* ):**
- sf::Vector2f **velocity():** returns the last calculated velocity

Also provided are the trigger functions. They are all void and lack parameters:
- **startUp()**
- **stopUp()**
- **startLeft()**
- **stopLeft()**
- **startDown()**
- **stopDown()**
- **startRight()**
- **stopRight()**