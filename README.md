## D3DHookMinesweeper
A very basic d3d hook.

The hack will show the board when at least one cell is revealed.

Aimbot: Press LSHIFT to use.

![screenshot](https://raw.githubusercontent.com/acquykhud/D3DHookMinesweeper/master/D3DHookMinesweeper/screenshot/screenshot.png)![](https://raw.githubusercontent.com/acquykhud/D3DHookMinesweeper/master/D3DHookMinesweeper/screenshot/aimbot.gif)
## How to use it ?
Compile in x64 mode, then use any injector to inject the dll to the game (I use RemoteDll).
Note: Keep the game's window at the smallest size, so that the render won't show bombs at wrong positions.
## What you need ?
 - Visual studio
 - Direct3d9 SDK June 2010
## Setup project
 - Make sure you have Direct3d9 SDK June 2010 installed.
 - Add these to your project properties "VC directories"
	 - Include directories: **$(DXSDK_DIR)Include**
	 - Library directories: **$(DXSDK_DIR)Lib\x64**
 - Then you good to go !!
## Additional 	library
 - Mhook (this supports x64 hook)
	 - [Mhook Github link](https://github.com/martona/mhook)
