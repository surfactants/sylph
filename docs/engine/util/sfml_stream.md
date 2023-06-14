# SFML_Stream
*header*
*engine/util/sfml_stream.hpp*

## About
Stream operators for various SFML types.

## Functions
### std::ostream& operator << ( *std::ostream& os, sf::Vector2<T> v* )
reads sf::Vector2 objects into stream with format "(x, y)"

### std::ostream& operator << ( *std::ostream& os, sf::Rect<T> r* )
	reads sf::Rect objects into stream with format "(left, top; width, height)"

### std::ostream& operator << ( *std::ostream& os, sf::Color c* )
reads sf::Color objects into stream with format "(r, g, b, a)"

---

[Module Engine](../engine.md)
[Library Util](util.md)
[Return to docs](../../docs.md)