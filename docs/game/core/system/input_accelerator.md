# Input_Accelerator
*class*
*game/system/input_accelerator.hpp*

## About
Accepts WASD-style input and calculates a movement vector. Despite residing in the *system/* directory, and being encapsulated by System_Manager, this class does not derive from System.

## Public Member Functions

### sf::Vector2f update( *const float delta_time* )
calculates and returns the framewise velocity

### void setSpeed( *float speed* )

### void setMaxSpeed( *float max_speed* )

### void setAcceleration( *float acceleration* )

### sf::Vector2f velocity()
returns the last calculated velocity

### Trigger Functions
- **startUp()**
- **stopUp()**
- **startLeft()**
- **stopLeft()**
- **startDown()**
- **stopDown()**
- **startRight()**
- **stopRight()**

## Example
In the prototype, the Accelerator is used to provide RTS-style camera movement, through the [Camera_Controller](camera_controller.md) class.

In **[System_Manager](../system_manager)::update()**, the vector is calculated, then passed to update the camera:
```
	sf::Vector2f v = accelerator.update(delta_time);
	camera_controller.update(v, mpos);
```

---

[Module Game](../../game.md)
[Submodule Core](../core.md)
[Return to Docs](../../../docs.md)