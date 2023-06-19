# Slider
*class : [Element](element.md)*  
*menu/elements/slider.hpp*

## About
Menu element providing a "slider" settings element, which allows selecting a number from 0-100.

Contains a function for effecting value changes. It's public; simply assign it after construction.

## Public Member Functions

### Slider() = default

### Slider( *std::string ntitle* )

### void set( *sf::Vector2f pos, const sf::Font& font* )
Loads fonts into text objects, and places them along with the shape objects.

Fonts are required for proper placement because spacing is determined by the size of the text objects.

### void findFill( *int mX* )

### float getFill()

### void scroll( *float delta* )

### virtual bool update( *const sf::Vector2i& mpos* )

### virtual void clickLeft()

### virtual void releaseLeft()

### void setFill( *float f* )

### float revert()

### void finalize()

---

[Module UI](../ui.md)  
[Submodule Elements](elements.md)  
[Return to Docs](../../docs.md)