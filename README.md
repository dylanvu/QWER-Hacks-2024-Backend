# QWER-Hacks-2024-Backend

## Resources
* Use this to test: https://websocketking.com/
* Even tho it is http, we can connnect via ws://localhost:3001/
* Unreal Websockets: https://www.youtube.com/watch?v=l9TTmtDBTWY
* UE freeze upon blueprint creation: https://forums.unrealengine.com/t/unreal-freezes-on-creating-blueprint-from-an-actor/1224255/29

## How to Attach Socket to an Actor
* Create a new actor class
* Attach the websocket code
* Place it using the `Place Actors` menu on the left
* See the ActorController files

## Scripts Dying After Laptop Unexpectedly Crashes
This is the weird cannot merge actions issue.

https://www.youtube.com/watch?v=kLcYipeEYDA
* Delete the following files:
    1. .vs
    2. Binaries
    3. Intermediate
    4. Saved
    5. the .sln file
* Hit yes when it asks to rebuild
* Regenerate Visual Studio Code