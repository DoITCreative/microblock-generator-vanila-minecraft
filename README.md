# Simple command generator, that will create structures from microblocks in vanila minecraft.

![MicroblockPNG](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview_world_1.png)

This program will allow users to create 3D objects layer by
layer in editor and generate list of commands to build that 
structures in game with command block.

#
![preview_editor_1_png](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview_editor_1.png)
![preview_editor_2_png](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview_editor_2.png)

## Currently written for unix only, any support with porting this program for windows will be awesome! :)

## Depends on:
- SDL
- SDL_image
- SDL_ttf

## Compilation from source:
- Clone repository (`git clone https://github.com/DoITCreative/microblock-generator-vanila-minecraft`)
- Install dependences with your package manager: apt, pacman, zypper, etc.
- Change directory to the project root (`cd microblock-generator-vanila-minecraft`)
- Run `make`

# How to use:
- Run `./microblockgen.out`
- Click on field to place block
- Click on placed block to remove it
- Click on bottom menu to select block to place
- Click on selected block in bottom menu to open block selection menu
- Change current layer by pressing arrows on the right side of the screen
- Set in world coordinates for structure on the bottom pannel
- You can save/load your constructions by pressing buttons with down and up arrows in the bottom menu
- When you are done, just quit, commands will be saved in "output.txt" in the same directory, where compiled program is.
- Put commands one by one in the command block in the game and activate command block with redstone signal after each command 
or use mrgarretto's command combiner "https://mrgarretto.com/cmdcombiner" to make commands much more compact.

## Command block required!

![MicroblockPNG2](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview_world_2.png)

Based on this in game command:
```
/summon armor_stand ~0.183f ~0.171f ~0f {Small:1, ShowArms:1, HandItems:[{id:log2,Damage:0,Count:1},{}], Pose:{RightArm:[-15f,0f,0f]}, Rotation:[45f], NoGravity:1b, Marker:1b, Invisible:1b, NoBasePlate:1f}
```


