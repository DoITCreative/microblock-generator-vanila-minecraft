# Simple command generator, that will create microblock structures in vanila minecraft.

![MicroblockPNG](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview2.png)

# Program is in alpha

This program will allow users to create structures layer by
layer in editor and generate list of commands to build that 
structures in game using command block.

![MicroblockPNG](https://github.com/DoITCreative/microblock-generator-vanila-minecraft/raw/master/docs/preview.png)

# How to use:
- Install microblockgen (see bellow how)
- Run ./microblockgen.out
- Click on field to place block
- Click on placed block to remove it
- Click on bottom menu to select block to place
- Click on selected block in bottom menu to open block select menu
- Change current layer by pressing arrows in the bottom menu
- You can save/load your constructions in bottom menu
- When you are done, just quit, commands will be saved in "output.txt"
- Put commands one by one in the command block in the game

## Command block required!

Based on this in game command:
```
/summon armor_stand ~0.183f ~0.171f ~0f {Small:1, ShowArms:1, HandItems:[{id:log2,Damage:0,Count:1},{}], Pose:{RightArm:[-15f,0f,0f]}, Rotation:[45f], NoGravity:1b, Marker:1b, Invisible:1b, NoBasePlate:1f}
```

## Depends on:
- SDL
- SDL_image
- SDL_ttf

## Installation process:
- Clone repository
- Run "make"
- Run ./microblockgen.out

