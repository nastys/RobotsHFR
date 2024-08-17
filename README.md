# RobotsHFR
60 FPS ASI Loader plugin for Robots (2005)   

Both the EU and the US versions are supported.   
Bigweld Chase runs at the original framerate (30 FPS).   

Uses Microsoft's [Detours](https://github.com/microsoft/Detours) library.   
Credits to ArkhanLight for the Cheat Engine table.

## Installing
- Install [Ultimate-ASI-Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader): copy the x86 (32-bit) DLL to the game folder, with the name "version.dll" if you have the EU version of the game, or "dinput8.dll" if you have the US version
- Create a folder called "plugins" inside the game folder and copy "robotshfr.asi" there

## Building
- Clone this repository with ``--recursive`` (or manually initialize the git modules afterwards)
- Open "Developer Command Prompt for VS 2022" in the "Detours" directory and run nmake
- Open robotshfr.sln in Visual Studio 2022 and build the solution
- If Visual Studio fails to automatically copy the files to the plugin folder after building, either take ownership of the "plugins" folder or run Visual Studio as administrator