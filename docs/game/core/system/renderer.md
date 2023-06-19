# Renderer
*class : System, sf::Drawable*  
*game/system/renderer.hpp*

Draws game objects in private Layer structures. Each Layer holds a pointer to an sf::View object, along with a vector of sf::Drawable pointers. The layers themselves are stored in a map structure, ensuring that index values always stay valid when removing a layer. 

## Public Member Functions
- void **add( *size_t layer, sf::Drawable* d* ):** Appends a drawable to the passed layer's vector
- void **setLayer( *size_t layer, sf::View\* view* ):**
- void **nullCheck():** iterates through the layers' drawable vectors and erases any nullptrs
- void **clear():** erases all layers
- void **clearLayer( *size_t layer* ):** removes the selected layer from the vector
- void **moveLayer( *size_t src, size_t target* ):**

---

[Module Game](../../game.md)  
[Submodule Core](../core.md)  
[Return to Docs](../../../docs.md)