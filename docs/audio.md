To add a sound:
- store the sound file in db/blob/audio/
- define in db/data/sounds.json
- run json-to-sqlite.exe and move the database
- record value in Event::Tag (engine/system/event/event.hpp)

To generate a sound:
- #include <system/event/event_bus.hpp>
- call the static function Event_Bus::publish(Event)
- construct an event:
-  - the constructor takes Event::Type, Event::Tag
-  - make the type Event::SOUND