# About SodiumUE4
An easy to use public and private cryptography plugin for Unreal Engine based on libsodium.

It currently works only on Win64 builds of Unreal Engine. Eventually Mac and Android is planned. The plugin is very simple (due to portable nature of libsodium), so it works on most versions of Unreal Engine.

**Supported versions:**
- Unreal Engine 5.6+ (tested with 5.6)
- Legacy UE4 support: Last tested on 4.19.2

## Installation

1. *git clone --recursive* this repo to your UnrealProject/Plugins/ folder.
2. Compile Source\ThirdParty\libsodium\libsodium.sln first, this will generate the sodium library. Use x64 and Release options as target.
3. Regenerate code for your Unreal Engine project (right click YourGame.uproject to do it)
4. Add "SodiumUE4" to YourGame.Build.cs in PublicDependencyModuleNames
5. Open and Build your game in Visual Studio or your IDE.
6. Start editor as usual, allow it to compile SodiumUE4, this should only happen once.
7. Build/Package your game as you normally would.

### License
https://opensource.org/licenses/MIT

### libsodium license:
https://opensource.org/licenses/ISC


# Usage

![Public encryption](http://i.imgur.com/ezgBj7v.jpg)
