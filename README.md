# SADX Sprite Rings

This mod replaces the rings in SADX with animated sprites. They're customizable by sub mods. Please check [here](#sub-mod-development) for information on creating sub mods.

It comes with several custom options built into the mod that can be used via the mod's configuration options. Users can also select the rendering method for the sprites, options exist for Point Filtering (default) and Linear Filtering.

## Sub Mod Development

Below will go over creating a sub mod that makes use of this mod's code to render a sprite. It's very simple, only needing to modify an ini file and adding your own textures.

### Getting Started
The easiest way to get started is to copy the `system` and `textures` folder from this mod's folder and paste them into your mod's root (the same folder your mod.ini file is located).

### INI Script
In the system folder, you'll find a `sprite.ini` file. This is how this mod creates the internal sprite setup for loading and displaying the sprite correctly. Below you'll find a copy of the script found in the system folder.

```ini
; Sprite Info Script
; This is the file loaded by the sadx-sprite-rings mod that's used to setup the animated sprite for rings and the collected effect.
;
; == Groups ==
; Object: Information for the Ring itself.
; Effect: Information for the effect played when a ring is collected.
; 
; == Elements ==
; Size: Size of the texture in pixels.
; TextureCount: Total textures used.
; FrameIncrement: How many frames pass between each changed frame of the animation. Not applicable to the Effect Group.
; SpriteScale: Size of the rendered sprite.


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

As provided in the comments in the script, you should be able to handle setup. A more detailed break down is below:

```
Header | Description
[Object]	| This header is information dedicated to the sprite for the ring.
[Effect]	| This header is information dedicated to the sprites used for the collection effect.

Info | Description | Object / Effect
Size			| This is the texture size in pixels, ie 16x16, 32x32. These are expected to be square textures, so you only need to include one value indicating the size. | Both
TextureCount	| This is the total number of textures being used in the sprite. Please make sure this is exactly the same are your textures otherwise your animation will display incorrectly, or potentially crash the game. | Both
FrameIncrement	| This sets how quickly the sprites animate. The full process is `(FrameCounterUnpaused / FrameIncrement) % TextureCount` which allows it to only increment when the game is not paused. | Object Only
SpriteScale		| This sets the size the sprites will be rendered at. The scale is relatable to the texture size. 0.3 works well for 16x16 sprites, 0.15 works well for 32x32, etc. | Both

```

