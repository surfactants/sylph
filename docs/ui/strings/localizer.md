# Localizer
*class*  
*ui/strings/localizer.hpp*

## About
Provides translated strings for text objects.

Also stores those text objects for simple language changes.

## Public Member Functions

### Localizer()
The constructor calls **load()** with no param

## std::string operator () ( *std::string key* )
Returns the localized string associated with the passed key.

## void record( *std::string key, sf::Text\* text* )
Records text objects for ease of language changes.

## void recordPersistent( *std::string key, sf::Text\* text* )
Records persistent text objects for ease of language changes.

Separate from the normal record to cut down on null checks (and subsequent removal of entries, which is a pain in a vector)

## void changeLanguage (*std::string language* )
Reloads the string map and applies it to records. Does not proceed if the selected language is already loaded.

## Private Member Functions

### void load( *std::string language = ""* )
Uses a [Database_Strings](../../engine/database/database_strings.md) object to get the current set of active strings.

An empty value loads the active language from the settings.

---

[Module UI](../ui.md)  
[Submodule Strings](strings.md)  
[Return to Docs](../../docs.md)