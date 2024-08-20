
# SADX Sprite Rings

This mod replaces the rings in SADX with animated sprites. They're customizable by sub mods. Please check [here](#sub-mod-development) for information on creating sub mods.

It comes with several custom options built into the mod that can be used via the mod's configuration options. Users can also select the rendering method for the sprites, options exist for Point Filtering (default) and Linear Filtering.

## Sub Mod Development

Below will go over creating a sub mod that makes use of this mod's code to render a sprite. It's very simple, only needing to modify an ini file and adding your own textures. Please check [Licensing](#licensing) for information on how crediting works.

### Getting Started
The easiest way to get started is to copy the `system` and `textures` folder from this mod's folder and paste them into your mod's root (the same folder your mod.ini file is located).

### Sprite Script
In the system folder, you'll find a `sprite.ini` file. This is how this mod creates the internal sprite setup for loading and displaying the sprite correctly. Below you'll find a copy of the script found in the system folder. This copy does not include the comments found in that file.

```ini
[Object]
Size=16
TextureCount=4
FrameIncrement=6
SpriteScale=0.3

[Effect]
Size=16
TextureCount=4
SpriteScale=0.3
```

A  detailed break down of each group and its variables are as follows:

| Header Section  | Description  |
|--|--|
| [Object] | This header is information dedicated to the sprite for the ring. |
| [Effect] | This header is information dedicated to the sprites used for the collection effect. |
---
| Variable | Description | Object / Effect |
|--|--|--|
| Size 				| This is the texture size in pixels, ie 16x16, 32x32. These are expected to be square textures, so you only need to include one value indicating the size. | Both 	|
| TextureCount 		| This is the total number of textures being used in the sprite. Please make sure this is exactly the same are your textures otherwise your animation will display incorrectly, or potentially crash the game. | Both 	|
| FrameIncrement 	| This sets how quickly the sprites animate. The full process is `(FrameCounterUnpaused / FrameIncrement) % TextureCount` which allows it to only increment when the game is not paused and stay within the boundaries of the total textures. | Object |
| SpriteScale 		| This sets the size the sprites will be rendered at. The scale is relatable to the texture size. 0.3 works well for 16x16 sprites, 0.15 works well for 32x32, etc. | Both 	|

### Additional Info
This mod removes the use of OBJ_REGULAR as the PVM used by the rings, instead opting for two unique PVMs, OBJ_RING and EFF_RING. These can be provided in any format (pvm, texpack, pvmx), but this mod has only been tested using texpacks and pvmx. You may experience more alpha related problems using pvm due to it being further compressed.

Ideally if you're developing a sub mod for this, you'll want to include this mod as a dependency. Please follow [this guide](https://github.com/X-Hax/SADXModdingGuide/wiki/Mod-Dependencies) for information on creating Mod Dependencies. This will prevent issues with users attempting to use your mod while not having this mod to make sure it runs.

Just like this mod, you can also include multiple configuration options. Please refer to the [Codeless Config](https://github.com/X-Hax/SADXModdingGuide/wiki/Setting-up-a-Mod-Config-File#codeless-configuration) setup for the Mod Manager. You can use this and the same basic folder structure used in the base mod to create configurable sprites for your mod. Inside of the include directories would be your `system` folder with the `sprite.ini` file, and your `textures` folder with your `texpack` or `pvmx` files. PVM files would go in the `system` folder.

### Issues
Please report all issues found to the [Issues](https://github.com/ItsEasyActually/SADXSpriteRings/issues) on this repository. Please know that there are known issues with alpha sorting. I have mitigated some of the issues, but others persist at this time. If you find spots to report an alpha issue, please check [this issue](https://github.com/ItsEasyActually/SADXSpriteRings/issues/1) and add a comment if you find any unlisted areas with alpha sorting issues.

### Licensing
This mod is licensed under the MIT License, you can read more in the `LICENSE.TXT` file. Credit is not required for sub mods as they do not modify the source code. Any modifications to the source code should include this licensing text and proper credit back to me is appreciated.
