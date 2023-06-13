# Color_Selector
*class : Menu_Element*
*menu/elements/color_selector.hpp*

Menu element which provides a color selection widget. Contains:
- [Button](button.md) for entry and preview
- saturation/value VertexArray where the actual selection occurs
- hue slider which modifies the colors of the VertexArray

The latter two elements are static. Each instance may define a position for them, which will be set on opening.

## Read more:
- [Menu Elements](elements.md)
- [Menus](../menu.md)