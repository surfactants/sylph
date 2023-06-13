# Collide
*header*
*engine/math/collide.hpp*

[Module Engine](../engine.md)  
[Library Math](math.md)

Checks intersections between SFML types. All functions are provided within the namespace **collide**.

- bool **convexShape_Point( *const sf::ConvexShape& shape, const sf::Vector2f point* ):** checks if the point is inside the shape
- std::pair<bool, sf::Vector2f> **twoLineSegments( *const sf::Vector2f& q, const sf::Vector2f&s, const sf::Vector2f& p, const sf::Vector2f& r* ):** checks the intersection of two line segments, defined as *(q, q + s)* and *p, p + r)*. The returned pair's bool indicates if an intersection exists. If true, the point of intersection is included. For an overview of how this algorithm works, please view [this StackOverflow answer](https://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect), which is where I learned it.
- bool **contains( *const sf::CircleShape& c, const sf::Vector2f& p* ):** checks if the point is inside the circle