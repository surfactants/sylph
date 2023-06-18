# Database
*interface*
*engine/database/database.hpp*

## About
Data storage in Sylph is handled through SQLite databases. Only the soundtrack is stored as plain files in the directory (as SFML can only stream music with direct file access).

The Database interface is concrete, but provides no public member functions other than a constructor and a destructor. The constructor accepts a filename string (defaults to "data.db", which is where base game data such as sounds, fonts, and worldgen rules are stored).

## Protected Member Functions
### void selectTable( *std::string table* )


### void selectByKey( *std::string table, std::string key* )


### void electByKey( *std::string table, int key* )


### bool tep()


### void inalize()


### void execute( *std::string sql* )


### std::string toString( *int column* )


### int toInt( *int column* )


### float toFloat( *int column* )


### Blob oBlob( *int row, const std::string column_name = "DATA"* )
Returns a Blob object for initializing objects such as textures, fonts, etc.

Blob is a protected struct containing a buffer object (std::shared_ptr<char[]>) along with the buffer's length (int). It has an optional constructor which accepts a length and initializes the buffer from it.

TODO link to json-to-sqlite docs

## Notes


---

[Module Engine](../engine.md)  
[Return to docs](../../docs.md)