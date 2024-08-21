
# SADX Sprite Rings

This mod replaces the rings in SADX with animated sprites. They're customizable by sub mods. Please check [here](#sub-mod-development) for information on creating sub mods.

It comes with several custom options built into the mod that can be used via the mod's configuration options. Users can also select the rendering method for the sprites, options exist for Point Filtering (default) and Linear Filtering. Users can also toggle if the ring's render with a shadow or not.

If you're playing this mod with any sub mods installed, please be aware the sub mods will take priority over all configurations.

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
ColorA=1.0
ColorR=1.0
ColorG=1.0
ColorB=1.0
ShadowScale=0.5

[Effect]
Size=16
TextureCount=4
SpriteScale=0.3
ColorA=1.0
ColorR=1.0
ColorG=1.0
ColorB=1.0
```

A  detailed break down of each group and its variables are as follows:

| Header Section  | Description  |
|--|--|
| [Object] | This header is information dedicated to the sprite for the ring. |
| [Effect] | This header is information dedicated to the sprites used for the collection effect. |
---
| Variable | Description | Default Value | Object / Effect |
|--|--|--|--|
| Size 				| This is the texture size in pixels, ie 16x16, 32x32. These are expected to be square textures, so you only need to include one value indicating the size.																						| 16	| Both 		|
| TextureCount 		| This is the total number of textures being used in the sprite. Please make sure this is exactly the same are your textures otherwise your animation will display incorrectly, or potentially crash the game.									| 4		| Both 		|
| FrameIncrement 	| This sets how quickly the sprites animate. The full process is `(FrameCounterUnpaused / FrameIncrement) % TextureCount` which allows it to only increment when the game is not paused and stay within the boundaries of the total textures.	| 6		| Object	|
| SpriteScale 		| This sets the size the sprites will be rendered at. The scale is relatable to the texture size. 0.3 works well for 16x16 sprites, 0.15 works well for 32x32, etc.																				| 0.3	| Both 		|
| ColorA			| This float value that sets the alpha amount for the sprite. 	| 1.0 | Both |
| ColorR			| This float value sets the red color amount for the sprite. 	| 1.0 | Both |
| ColorG			| This float value sets the green color amount for the sprite. 	| 1.0 | Both |
| ColorB			| This float value sets the blue color amount for the sprite. 	| 1.0 | Both |
| ShadowScale		| This float value sets the scale of ring's shadow. 			| 0.5 | Object |

**Note 1: Variables with Both work for both elements, any that specify being on one or the other only have an applicable effect to that element.**\
**Note 2: The Texture Count, as stated, must match to render correctly. If you have less textures than the count, it will crash. If you have more than the count, it will not display properly.**\

### Additional Configurations
Just like this mod does, you can also include multiple configuration options in your sub mod. Please refer to the [Codeless Config](https://github.com/X-Hax/SADXModdingGuide/wiki/Setting-up-a-Mod-Config-File#codeless-configuration) setup for the Mod Manager.

### Textures
This mod removes the use of OBJ_REGULAR as the PVM used by the rings, instead opting for two unique PVMs, OBJ_RING and EFF_RING. These can be provided in any format (`pvm`, `texpack`, `pvmx`), but this mod has only been tested using `texpacks` and `pvmx`. You may experience more alpha related problems using `pvm` due to it being a lossy format.

If you're using `texpacks` or `pvmx`, these will go in your mod's `textures` folder just like this mod does. If you're using `pvm`, those will be placed in your sub mod's `system` folder. 

You're able to have as many textures (frames really) in these as long as you update the script accordingly.

### Using Coloring
Sprites can be colored using a supplied ARGB value in its section. This color will overlay on top of the existing sprite colors, so this will typically be best left at 1.0 for all values (You don't need to include those in a script, they will default to 1.0 if not included). If you check the sprites included in the `mario64`, `mario64-red`, or `mario64-blue` folders, you'll find sprites that are ideal for using with this coloring, and those configurations make use of that. 

If you are making a sub mod and you intend to do something similar to how the `mario64` options work, you can just include a single set of textures and format your configurable include directories to have a `sprite.ini` file in the `system` folder with the coloring you want to use. This can reduce the number of texture files you'd need to include.

### Dependencies
Ideally if you're developing a sub mod for this, you'll want to include this mod as a dependency. Please follow [this guide](https://github.com/X-Hax/SADXModdingGuide/wiki/Mod-Dependencies) for information on creating Mod Dependencies. This will prevent issues with users attempting to use your mod while not having this mod to make sure it runs. 

## Issues
Please report all issues found to the [Issues](https://github.com/ItsEasyActually/SADXSpriteRings/issues) on this repository. Please know that there are known issues with alpha sorting. I have mitigated some of the issues, but others persist at this time. If you find spots to report an alpha issue, please check [this issue](https://github.com/ItsEasyActually/SADXSpriteRings/issues/1) and add a comment if you find any unlisted areas with alpha sorting issues.

## Licensing
This mod is licensed under the MIT License, you can read more in the `LICENSE.TXT` file. Credit is not required for sub mods as they do not modify the source code. Any modifications to the source code should include this licensing text and proper credit back to me is appreciated.
