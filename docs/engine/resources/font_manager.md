# Font_Manager
*class*
*engine/resources/font_manager.hpp*

## About
Singleton that contains and provides sf::Font objects. Also stores the associated font buffers.

Access is provided with the associated enumerated type, *Font* (*engine/resources/font.hpp*), through the only public member function:

### static sf::Font\* get( *Font f* )
returns a pointer to an sf::Font object based on the passed font key

---

[Module Engine](../engine.md)  
[Submodule Resources](resources.md)  
[Return to docs](../../docs.md)