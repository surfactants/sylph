# Audio
*submodule*  
*engine/audio/*

## About
Audio is handled through the [event bus](../event/event_bus.md), with the sound and music players acting as listeners.

## Sound_Player
The sound player listens for events of type Event::SOUND. It selects which sound to play from the event's tag.

To add a sound, first add the relevant data:
- record value in Event::Tag (engine/system/event/event.hpp)
- add to data.db's SOUNDS table
- - TAG TEXT, SOURCE TEXT, THRESHOLD REAL, and DATA BLOB fields
- - with json-to-sqlite:
- - - store the sound file in db/blob/audio/
- - - define in db/data/sounds.json
- - - run json-to-sqlite.exe and move the database

Add to database with json-to-sqlite:

To set a trigger for the sound:
- #include <system/event/event_bus.hpp>
- call Event_Bus::publish(Event); static
- construct an event:
- - the constructor takes Event::Type, Event::Tag
- - make the type Event::SOUND
- - the tag should correspond to what was added in the first part.

## Music_Player
The music player has two modes: "Title", played in the main menu, and "Game", played in-game (and from the pause menu). Finer control will be added in a later version. Currently can only handle **.wav** files.

To add a song,
- add to the *soundtrack/* directory.
- title track is named "menu.wav"; game tracks are numbered (1.wav, 2.wav, etc.) and will play sequentially in-game.

---

[Module Engine](../engine.md)  
[Return to docs](../../docs.md)