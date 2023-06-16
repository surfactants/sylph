# Main_State
*class*
*engine/shell/main_state.hpp*

## About
Abstract class 

## Public Member Functions

### virtual void update( *const float delta_time* )
*Pure*

### virtual void handleInput( *const sf::Event& event* )
*Pure*

### virtual void windowResize( *const sf::Vector2u& w_size* )
*Pure*

### static std::function<void( *Main_State::State* )> setState

## Private Member Functions

### virtual void draw( *sf::RenderTarget& target, sf::RenderStates states* ) const

## Protected Members

### std::vector<const sf::Drawable\*> drawables

### sf::View view

---

[Module Engine](../engine.md)  
[Submodule Shell](shell.md)  
[Return to docs](../../docs.md)