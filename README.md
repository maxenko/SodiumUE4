# libsodium-ue4
An easy to use public and private cryptography plugin for Unreal Engine 4 based on libsodium.

Look for stable branch in the future as this gets developed. Master branch is beta. It currently works only on Win64 builds of UE4. Eventually Mac and Android is planned, but not for a while.

## Installation

1. Clone this repo to your UnrealProject/Plugins/SodiumUE4/ folder.
2. Compile Source/ThirdParty/SodiumUE4Library/libsodiumUE4.sln first, this will generate the sodium library. Use x64 and Release options as target.
3. Regenerate code for your UE4 project (right click YourGame.uproject to do it)
4. Add "SodiumUE4" to YourGame.Build.cs in PrivateDependencyModuleNames
5. Open and Build your game in Visual Studio.
6. Start editor as usual, allow it to compile SodiumUE4.
7. To have this plugin work in packaged game, copy libsodiumUE4.dll to the same location as YourGame-Win64-Shipping.exe

I know its not 100% automated yet, if you know how to package this better - please fork it. I am unlikely to do it anytime soon.

If you can help improving this readme, please pull.

### License
https://opensource.org/licenses/MIT

### libsodium license:
https://opensource.org/licenses/ISC


#Usage

![Public encryption](http://i.imgur.com/ezgBj7v.jpg)
