# Database
*interface*
*engine/database/database.hpp*

[Module Engine](../engine.md)

Data storage in Sylph is handled through SQLite databases. Only the soundtrack is stored as plain files in the directory (as SFML can only stream music with direct file access).

The Database interface is concrete, but provides no public member functions other than a constructor and a destructor. The constructor accepts a filename string (defaults to "data.db", which is where base game data such as sounds, fonts, and worldgen rules are stored).

Derivations make use of the following protected member functions:
- void **selectTable( *std::string table* ):**
- void **selectByKey( *std::string table, std::string key* ):**
- void **selectByKey( *std::string table, int key* ):**
- bool **step():**
- void **finalize():**
- void **execute( *std::string sql* ):**
- std::string **toString( *int column* ):**
- int **toInt( *int column* ):**
- float **toFloat( *int column* ):**
- Blob **toBlob( *int row, const std::string column_name = "DATA"* ):** Blob is a protected struct containing a buffer object (std::shared_ptr<char[]>) along with the buffer's length. 

TODO link to json-to-sqlite docs