# Primordial
*header*
*engine/math/primordial.hpp*

## About
Functions for basic math operations.

## Functions
### T scalarDistance( *const sf::Vector2<T> v, const sf::Vector2<T> w* )
calculates a scalar (single-value) distance between two sf::Vector2 points.

### T sf::Vector2<T> vectorDistance( *const sf::Vector2<T> v, const sf::Vector2<T> w* )
calculates a vector distance between two sf::Vector2 points.

### int sign( *T val* )
calculates a normalized sign integer. i.e. sign(-0.1) returns -1, sign(5) returns 1, etc.

### int roundFloat( *float f* )
sign-sensitive float-to-int rounding

### sf::Vector2f alculateMoveVector( *float angle, float velocity* )
calculates a velocity vector based on an actor's orientation and scalar velocity.

---

[Module Engine](../engine.md)  
[Library Math](math.md)  
[Return to docs](../../docs.md)
