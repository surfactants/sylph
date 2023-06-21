# Database
*submodule*  
*engine/database/database.hpp*

## About
Data storage in Sylph is handled through SQLite databases. Only the soundtrack is stored as plain files (as SFML can only stream music with direct file access). These databases are accessed through the Database interface.

While the interface is concrete, it is strictly intended for derived use, providing no public member functions other than a constructor and a destructor. The constructor accepts a filename string (defaults to "data.db", which is where base game data such as sounds, fonts, and worldgen rules are stored).

## Protected Member Functions
### void selectTable( *std::string table* )


### void selectByKey( *std::string table, std::string key* )


### void selectByKey( *std::string table, int key* )


### bool step()


### void finalize()


### void execute( *std::string sql* )


### std::string toString( *int column* )


### int toInt( *int column* )


### float toFloat( *int column* )


### Blob toBlob( *int row, const std::string column_name = "DATA"* )
Returns a Blob object for initializing objects such as textures, fonts, etc.

Blob is a protected struct containing a buffer object (std::shared_ptr<char[]>) along with the buffer's length (int). It has an optional constructor which accepts a length and initializes the buffer from it.

Because the Blob's buffer memory is automatically managed, it *must* be stored for objects that call for it, such as sf::Font.

TODO link to json-to-sqlite docs

## Notes


---

[Module Engine](../engine.md)  
[Return to docs](../../docs.md)