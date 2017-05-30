#include "sdlinterface.h"
#include "block.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdlib.h>


/*
 *	Bugs: 
 *	1) More then 1 block placing with using rect and line tools over placed blocks
 *	2) Crash after 48 layer changes	
 */

int toolselected = 0; //0 - point, 1 - line, 2 - rectangle
int tile_select_point_X = 0; //Point to mark position for line and rectangle tools.
int tile_select_point_Y = 0;
int tile_select_point_Z = 0;

int tile_select_point_previous_X = 0; //Point to first mark position for line and rectangle tools.
int tile_select_point_previous_Y = 0;
int tile_select_point_previous_Z = 0;

bool tile_select_point_was_set = false; //Checks if mark was set

//Files


//Main function in this class
Sdlinterface::Sdlinterface()
{
	bool quit = false; //Variable to check if it is time to quit or not
	menuopened=false; //Variable to check if block select menu is opened
	init(); //Initializes SDL

	//Fills bottom menu vector with blocks
	slots.push_back("textures/brick.png");
	slots.push_back("textures/cobblestone.png");
	slots.push_back("textures/diamond_block.png");
	slots.push_back("textures/dirt.png");
	slots.push_back("textures/glass.png");
	slots.push_back("textures/glowstone.png");
	slots.push_back("textures/gold_block.png");
	slots.push_back("textures/hay_block_side.png");
	slots.push_back("textures/iron_block.png");
	slots.push_back("textures/log_acacia.png");
	slots.push_back("textures/log_birch.png");

	//Fills id vector for blocks
	ids.push_back("brick");
	ids.push_back("cobblestone");
	ids.push_back("diamond_block");
	ids.push_back("dirt");
	ids.push_back("glass");
	ids.push_back("glowstone");
	ids.push_back("gold_block");
	ids.push_back("hay_block");
	ids.push_back("iron_block");
	ids.push_back("log2");
	ids.push_back("log");

	//Fills damage vector for blocks
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(0);
	damage.push_back(2);

	all_ids.push_back("bone_block_top");
	all_ids.push_back("bookshelf");
	all_ids.push_back("brick_block");
	all_ids.push_back("clay");
	all_ids.push_back("coal_block");
	all_ids.push_back("coal_ore");
	all_ids.push_back("dirt");
	all_ids.push_back("cobblestone");
	all_ids.push_back("mossy_cobblestone");
	all_ids.push_back("crafting_table");
	all_ids.push_back("diamond_block");
	all_ids.push_back("diamond_ore");
	all_ids.push_back("dirt");
	all_ids.push_back("dirt");
	all_ids.push_back("emerald_block");
	all_ids.push_back("emerald_ore");
	all_ids.push_back("end_bricks");
	all_ids.push_back("end_stone");
	all_ids.push_back("glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("stained_glass");
	all_ids.push_back("glowstone");
	all_ids.push_back("gold_block");
	all_ids.push_back("gold_ore");
	all_ids.push_back("gravel");
	all_ids.push_back("hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("stained_hardened_clay");
	all_ids.push_back("hay_block");
	all_ids.push_back("ice");
	all_ids.push_back("packed_ice");
	all_ids.push_back("iron_block");
	all_ids.push_back("iron_ore");
	all_ids.push_back("lapis_block");
	all_ids.push_back("lapis_ore");
	all_ids.push_back("log2");
	all_ids.push_back("log2");
	all_ids.push_back("log");
	all_ids.push_back("log");
	all_ids.push_back("log");
	all_ids.push_back("log");
	all_ids.push_back("melon_block");
	all_ids.push_back("mycelium");
	all_ids.push_back("nether_brick");
	all_ids.push_back("netherrack");
	all_ids.push_back("obsidian");
	all_ids.push_back("planks");
	all_ids.push_back("planks");
	all_ids.push_back("planks");
	all_ids.push_back("planks");
	all_ids.push_back("planks");
	all_ids.push_back("planks");
	all_ids.push_back("prismarine");
	all_ids.push_back("prismarine");
	all_ids.push_back("prismarine");
	all_ids.push_back("pumpkin");
	all_ids.push_back("lit_pumpkin");
	all_ids.push_back("purpur_pillar");
	all_ids.push_back("quartz_block");
	all_ids.push_back("quartz_block");
	all_ids.push_back("quartz_block");
	all_ids.push_back("quartz_ore");
	all_ids.push_back("red_nether_brick");
	all_ids.push_back("sand");
	all_ids.push_back("red_sandstone");
	all_ids.push_back("red_sandstone");
	all_ids.push_back("red_sandstone");
	all_ids.push_back("redstone_block");
	all_ids.push_back("redstone_lamp");
	all_ids.push_back("redstone_ore");
	all_ids.push_back("sand");
	all_ids.push_back("sandstone");
	all_ids.push_back("sandstone");
	all_ids.push_back("sandstone");
	all_ids.push_back("slime");
	all_ids.push_back("snow");
	all_ids.push_back("soul_sand");
	all_ids.push_back("sponge");
	all_ids.push_back("sponge");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stone");
	all_ids.push_back("stonebrick");
	all_ids.push_back("stonebrick");
	all_ids.push_back("stonebrick");
	all_ids.push_back("stonebrick");
	all_ids.push_back("tnt");
	all_ids.push_back("wool_colored_black");
	all_ids.push_back("wool_colored_blue");
	all_ids.push_back("wool_colored_brown");
	all_ids.push_back("wool_colored_cyan");
	all_ids.push_back("wool_colored_gray");
	all_ids.push_back("wool_colored_green");
	all_ids.push_back("wool_colored_light_blue");
	all_ids.push_back("wool_colored_lime");
	all_ids.push_back("wool_colored_magenta");
	all_ids.push_back("wool_colored_orange");
	all_ids.push_back("wool_colored_pink");
	all_ids.push_back("wool_colored_purple");
	all_ids.push_back("wool_colored_red");
	all_ids.push_back("wool_colored_silver");
	all_ids.push_back("wool_colored_white");
	all_ids.push_back("wool_colored_yellow");

	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(15);
	all_damage.push_back(11);
	all_damage.push_back(12);
	all_damage.push_back(9);
	all_damage.push_back(7);
	all_damage.push_back(13);
	all_damage.push_back(3);
	all_damage.push_back(5);
	all_damage.push_back(2);
	all_damage.push_back(1);
	all_damage.push_back(6);
	all_damage.push_back(10);
	all_damage.push_back(14);
	all_damage.push_back(8);
	all_damage.push_back(0);
	all_damage.push_back(4);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(15);
	all_damage.push_back(11);
	all_damage.push_back(12);
	all_damage.push_back(9);
	all_damage.push_back(7);
	all_damage.push_back(13);
	all_damage.push_back(3);
	all_damage.push_back(5);
	all_damage.push_back(2);
	all_damage.push_back(1);
	all_damage.push_back(6);
	all_damage.push_back(10);
	all_damage.push_back(14);
	all_damage.push_back(8);
	all_damage.push_back(0);
	all_damage.push_back(4);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(2);
	all_damage.push_back(3);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(4);
	all_damage.push_back(5);
	all_damage.push_back(2);
	all_damage.push_back(3);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(7);
	all_damage.push_back(0);
	all_damage.push_back(0);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(5);
	all_damage.push_back(6);
	all_damage.push_back(3);
	all_damage.push_back(4);
	all_damage.push_back(1);
	all_damage.push_back(2);
	all_damage.push_back(0);
	all_damage.push_back(3);
	all_damage.push_back(2);
	all_damage.push_back(1);
	all_damage.push_back(0);
	all_damage.push_back(15);
	all_damage.push_back(11);
	all_damage.push_back(12);
	all_damage.push_back(9);
	all_damage.push_back(7);
	all_damage.push_back(13);
	all_damage.push_back(3);
	all_damage.push_back(5);
	all_damage.push_back(2);
	all_damage.push_back(1);
	all_damage.push_back(6);
	all_damage.push_back(10);
	all_damage.push_back(14);
	all_damage.push_back(8);
	all_damage.push_back(0);
	all_damage.push_back(4);

	//Fills block select menu with blocks
	all_blocks.push_back("textures/bone_block_top.png");
	all_blocks.push_back("textures/bookshelf.png");
	all_blocks.push_back("textures/brick.png");
	all_blocks.push_back("textures/clay.png");
	all_blocks.push_back("textures/coal_block.png");
	all_blocks.push_back("textures/coal_ore.png");
	all_blocks.push_back("textures/coarse_dirt.png");
	all_blocks.push_back("textures/cobblestone.png");
	all_blocks.push_back("textures/cobblestone_mossy.png");
	all_blocks.push_back("textures/crafting_table_front.png");
	all_blocks.push_back("textures/diamond_block.png");
	all_blocks.push_back("textures/diamond_ore.png");
	all_blocks.push_back("textures/dirt.png");
	all_blocks.push_back("textures/dirt_podzol_top.png");
	all_blocks.push_back("textures/emerald_block.png");
	all_blocks.push_back("textures/emerald_ore.png");
	all_blocks.push_back("textures/end_bricks.png");
	all_blocks.push_back("textures/end_stone.png");
	all_blocks.push_back("textures/glass.png");
	all_blocks.push_back("textures/glass_black.png");
	all_blocks.push_back("textures/glass_blue.png");
	all_blocks.push_back("textures/glass_brown.png");
	all_blocks.push_back("textures/glass_cyan.png");
	all_blocks.push_back("textures/glass_gray.png");
	all_blocks.push_back("textures/glass_green.png");
	all_blocks.push_back("textures/glass_light_blue.png");
	all_blocks.push_back("textures/glass_lime.png");
	all_blocks.push_back("textures/glass_magenta.png");
	all_blocks.push_back("textures/glass_orange.png");
	all_blocks.push_back("textures/glass_pink.png");
	all_blocks.push_back("textures/glass_purple.png");
	all_blocks.push_back("textures/glass_red.png");
	all_blocks.push_back("textures/glass_silver.png");
	all_blocks.push_back("textures/glass_white.png");
	all_blocks.push_back("textures/glass_yellow.png");
	all_blocks.push_back("textures/glowstone.png");
	all_blocks.push_back("textures/gold_block.png");
	all_blocks.push_back("textures/gold_ore.png");
	all_blocks.push_back("textures/gravel.png");
	all_blocks.push_back("textures/hardened_clay.png");
	all_blocks.push_back("textures/hardened_clay_stained_black.png");
	all_blocks.push_back("textures/hardened_clay_stained_blue.png");
	all_blocks.push_back("textures/hardened_clay_stained_brown.png");
	all_blocks.push_back("textures/hardened_clay_stained_cyan.png");
	all_blocks.push_back("textures/hardened_clay_stained_gray.png");
	all_blocks.push_back("textures/hardened_clay_stained_green.png");
	all_blocks.push_back("textures/hardened_clay_stained_light_blue.png");
	all_blocks.push_back("textures/hardened_clay_stained_lime.png");
	all_blocks.push_back("textures/hardened_clay_stained_magenta.png");
	all_blocks.push_back("textures/hardened_clay_stained_orange.png");
	all_blocks.push_back("textures/hardened_clay_stained_pink.png");
	all_blocks.push_back("textures/hardened_clay_stained_purple.png");
	all_blocks.push_back("textures/hardened_clay_stained_red.png");
	all_blocks.push_back("textures/hardened_clay_stained_silver.png");
	all_blocks.push_back("textures/hardened_clay_stained_white.png");
	all_blocks.push_back("textures/hardened_clay_stained_yellow.png");
	all_blocks.push_back("textures/hay_block_side.png");
	all_blocks.push_back("textures/ice.png");
	all_blocks.push_back("textures/ice_packed.png");
	all_blocks.push_back("textures/iron_block.png");
	all_blocks.push_back("textures/iron_ore.png");
	all_blocks.push_back("textures/lapis_block.png");
	all_blocks.push_back("textures/lapis_ore.png");
	all_blocks.push_back("textures/log_acacia.png");
	all_blocks.push_back("textures/log_big_oak.png");
	all_blocks.push_back("textures/log_oak.png");
	all_blocks.push_back("textures/log_birch.png");
	all_blocks.push_back("textures/log_jungle.png");
	all_blocks.push_back("textures/log_spruce.png");
	all_blocks.push_back("textures/melon_side.png");
	all_blocks.push_back("textures/mycelium_side.png");
	all_blocks.push_back("textures/nether_brick.png");
	all_blocks.push_back("textures/netherrack.png");
	all_blocks.push_back("textures/obsidian.png");
	all_blocks.push_back("textures/planks_acacia.png");
	all_blocks.push_back("textures/planks_big_oak.png");
	all_blocks.push_back("textures/planks_birch.png");
	all_blocks.push_back("textures/planks_jungle.png");
	all_blocks.push_back("textures/planks_oak.png");
	all_blocks.push_back("textures/planks_spruce.png");
	all_blocks.push_back("textures/prismarine_rough.png");
	all_blocks.push_back("textures/prismarine_bricks.png");
	all_blocks.push_back("textures/prismarine_dark.png");
	all_blocks.push_back("textures/pumpkin_face_off.png");
	all_blocks.push_back("textures/pumpkin_face_on.png");
	all_blocks.push_back("textures/purpur_pillar.png");
	all_blocks.push_back("textures/quartz_block_bottom.png");
	all_blocks.push_back("textures/quartz_block_chiseled.png");
	all_blocks.push_back("textures/quartz_block_lines.png");
	all_blocks.push_back("textures/quartz_ore.png");
	all_blocks.push_back("textures/red_nether_brick.png");
	all_blocks.push_back("textures/red_sand.png");
	all_blocks.push_back("textures/red_sandstone_carved.png");
	all_blocks.push_back("textures/red_sandstone_normal.png");
	all_blocks.push_back("textures/red_sandstone_smooth.png");
	all_blocks.push_back("textures/redstone_block.png");
	all_blocks.push_back("textures/redstone_lamp_off.png");
	all_blocks.push_back("textures/redstone_ore.png");
	all_blocks.push_back("textures/sand.png");
	all_blocks.push_back("textures/sandstone_carved.png");
	all_blocks.push_back("textures/sandstone_normal.png");
	all_blocks.push_back("textures/sandstone_smooth.png");
	all_blocks.push_back("textures/slime.png");
	all_blocks.push_back("textures/snow.png");
	all_blocks.push_back("textures/soul_sand.png");
	all_blocks.push_back("textures/sponge.png");
	all_blocks.push_back("textures/sponge_wet.png");
	all_blocks.push_back("textures/stone.png");
	all_blocks.push_back("textures/stone_andesite.png");
	all_blocks.push_back("textures/stone_andesite_smooth.png");
	all_blocks.push_back("textures/stone_diorite.png");
	all_blocks.push_back("textures/stone_diorite_smooth.png");
	all_blocks.push_back("textures/stone_granite.png");
	all_blocks.push_back("textures/stone_granite_smooth.png");
	all_blocks.push_back("textures/stonebrick.png");
	all_blocks.push_back("textures/stonebrick_carved.png");
	all_blocks.push_back("textures/stonebrick_cracked.png");
	all_blocks.push_back("textures/stonebrick_mossy.png");
	all_blocks.push_back("textures/tnt_side.png");
	all_blocks.push_back("textures/wool_colored_black.png");
	all_blocks.push_back("textures/wool_colored_blue.png");
	all_blocks.push_back("textures/wool_colored_brown.png");
	all_blocks.push_back("textures/wool_colored_cyan.png");
	all_blocks.push_back("textures/wool_colored_gray.png");
	all_blocks.push_back("textures/wool_colored_green.png");
	all_blocks.push_back("textures/wool_colored_light_blue.png");
	all_blocks.push_back("textures/wool_colored_lime.png");
	all_blocks.push_back("textures/wool_colored_magenta.png");
	all_blocks.push_back("textures/wool_colored_orange.png");
	all_blocks.push_back("textures/wool_colored_pink.png");
	all_blocks.push_back("textures/wool_colored_purple.png");
	all_blocks.push_back("textures/wool_colored_red.png");
	all_blocks.push_back("textures/wool_colored_silver.png");
	all_blocks.push_back("textures/wool_colored_white.png");
	all_blocks.push_back("textures/wool_colored_yellow.png");

	load_resources();

	render(); //Redraws screen
	while (quit == false)
	{
		while (SDL_PollEvent(&event)) //Checks events
		{
			if (event.type == SDL_QUIT) //On "x"(Quit) button pressed
			{
				//Saves blocks to output file
				writeCommandToFile("output.txt");
				//Unload block_list from memory
				for (Block* b:block_list)
				{
					delete(b);
				}
				quit = true;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN) //On mouse pressed
			{
				if (event.button.button == SDL_BUTTON_LEFT) //On left click
				{
					if (event.button.x<=625 && event.button.y<=425) //Boundaries of block placing field
					{
						if (menuopened) //If menu is opened do stuff there
						{
							if (event.button.x>28 && event.button.x<595 && event.button.y>25 && event.button.y<400) //Checks click on blocks in block select menu
							{
								int xclick=(int)((event.button.x-28)/32);
								int yclick=(int)((event.button.y-25)/32);
								if (yclick*18+xclick<all_blocks.size())
								{
									slots.at(selector_pos)=all_blocks.at(yclick*18+xclick); //Changes picture on bottom pannel, where sector points
									ids.at(selector_pos)=all_ids.at(yclick*18+xclick); //Changes picture on bottom pannel, where sector points
									damage.at(selector_pos)=all_damage.at(yclick*18+xclick); //Changes picture on bottom pannel, where sector points
									menuopened=false;
								}
								render();
							}
						}
						else
						{   // Block select menu is closed
							
							//Transforms coordinates of click to grid coordinates
							int coord_click_x=(int)(event.button.x/25); 
							int coord_click_y=(int)(event.button.y/25);
							bool isset=false; //Block is drawn or not
							int counter=0;
							for (Block* b:block_list) //Check all drawn blocks
							{
								if (b->getX()==coord_click_x && b->getY()==coord_click_y && b->getZ()==layer) //If block is drawn, erase it
								{
									block_list.erase(block_list.begin()+counter);
									counter=-1;
									delete(b);
									isset=true;
								}
								counter++;
							}
							if (!isset&&!menuopened)
							{
								Block* b;

								if (toolselected == 0)
								{
									//Places block from selector to the grid
									b = new Block(coord_click_x,coord_click_y,layer,damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
									block_list.push_back(b);
								}

								if (toolselected>0 && !(tile_select_point_X==coord_click_x && tile_select_point_Y==coord_click_y && tile_select_point_Z==layer) && !tile_select_point_was_set) //Selected tool is not point
								{

									tile_select_point_X=coord_click_x; //Places marker
									tile_select_point_Y=coord_click_y;
									tile_select_point_Z=layer;

									tile_select_point_previous_X=tile_select_point_X; //Store previous coords
									tile_select_point_previous_Y=tile_select_point_Y;
									tile_select_point_previous_Z=tile_select_point_Z;

									tile_select_point_was_set = true;
								}
								else if (tile_select_point_was_set)
								{

									switch (toolselected)
									{
										case 1:
											if (tile_select_point_previous_X==coord_click_x)
											{
												for (int i=minimum(tile_select_point_previous_Y,coord_click_y);i<=maximum(tile_select_point_previous_Y,coord_click_y);i++)
												{
													b = new Block(tile_select_point_previous_X,i,layer,damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
													block_list.push_back(b);
												}
											} 
											else
											{
												    int i, dx, dy, dz, l, m, n, x_inc, y_inc, z_inc, err_1, err_2, dx2, dy2, dz2;
    												int point[3];
    												
    												point[0] = tile_select_point_previous_X;
    												point[1] = tile_select_point_previous_Y;
    												point[2] = tile_select_point_previous_Z;
    												dx = coord_click_x - tile_select_point_previous_X;
    												dy = coord_click_y - tile_select_point_previous_Y;
    												dz = layer - tile_select_point_previous_Z;
    												x_inc = (dx < 0) ? -1 : 1;
    												l = abs(dx);
    												y_inc = (dy < 0) ? -1 : 1;
    												m = abs(dy);
    												z_inc = (dz < 0) ? -1 : 1;
    												n = abs(dz);
    												dx2 = l << 1;
    												dy2 = m << 1;
    												dz2 = n << 1;
    												
    												if ((l >= m) && (l >= n)) 
													{
    												    err_1 = dy2 - l;
    												    err_2 = dz2 - l;
    												    for (i = 0; i < l; i++) 
														{
															b = new Block(point[0],point[1],point[2],damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
															block_list.push_back(b);
    												        if (err_1 > 0) 
															{
    												            point[1] += y_inc;
    												            err_1 -= dx2;
    												        }
    												        if (err_2 > 0) 
															{
    												            point[2] += z_inc;
    												            err_2 -= dx2;
    												        }
    												        err_1 += dy2;
    												        err_2 += dz2;
    												        point[0] += x_inc;
    												    }
    												} 
													else if ((m >= l) && (m >= n)) 
													{
    												    err_1 = dx2 - m;
    												    err_2 = dz2 - m;
    												    for (i = 0; i < m; i++) 
														{
															b = new Block(point[0],point[1],point[2],damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
															block_list.push_back(b);
    												        if (err_1 > 0) 
															{
    												            point[0] += x_inc;
    												            err_1 -= dy2;
    												        }
    												        if (err_2 > 0) 
															{
    												            point[2] += z_inc;
    												            err_2 -= dy2;
    												        }
    												        err_1 += dx2;
    												        err_2 += dz2;
    												        point[1] += y_inc;
    												    }
    												} 
													else 
													{
    												    err_1 = dy2 - n;
    												    err_2 = dx2 - n;
    												    for (i = 0; i < n; i++) 
														{
															b = new Block(point[0],point[1],point[2],damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
															block_list.push_back(b);
    												        if (err_1 > 0) 
															{
    												            point[1] += y_inc;
    												            err_1 -= dz2;
    												        }
    												        if (err_2 > 0) 
															{
    												            point[0] += x_inc;
    												            err_2 -= dz2;
    												        }
    												        err_1 += dy2;
    												        err_2 += dx2;
    												        point[2] += z_inc;
    												    }
    												}
													b = new Block(point[0],point[1],point[2],damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
													block_list.push_back(b);
											}
											break;
										case 2:
											for (int zn=minimum(tile_select_point_previous_Z,layer);zn<=maximum(tile_select_point_previous_Z,layer);zn++)
											{
												for (int yn=minimum(tile_select_point_previous_Y,coord_click_y);yn<=maximum(tile_select_point_previous_Y,coord_click_y);yn++)
												{
													for (int xn=minimum(tile_select_point_previous_X,coord_click_x);xn<=maximum(tile_select_point_previous_X,coord_click_x);xn++)
													{
														b = new Block(xn,yn,zn,damage.at(selector_pos),ids.at(selector_pos),slots.at(selector_pos));
														block_list.push_back(b);

													}
												}
											}
											break;
									}

									tile_select_point_was_set = false;
								}
								else
								{
									tile_select_point_was_set = false;
								}
							}
							render();
						}
					}
					if (event.button.x<=625 && event.button.y>425 && event.button.y<475) //If bottom menu is clicked
					{
						if (event.button.x<395) //Clicked on block in bottom menu
						{
							if(selector_pos!=(int)((event.button.x-10)/35)) //Put selector on click place
							{
								selector_pos=(int)((event.button.x-10)/35);
							}
							else
							{
								if (menuopened) //Opens menu to select block
								{
									menuopened=false;
									render();
								}
								else
								{
									menuopened=true;
								}
							}
						}

						if (event.button.x>395&&event.button.x<430) //Point tool
						{
							toolselected = 0;
						}

						if (event.button.x>430&&event.button.x<465) //Line tool
						{
							toolselected = 1;
						}

						if (event.button.x>465&&event.button.x<500) //Rectangle tool
						{
							toolselected = 2;
						}

						if (event.button.x>500&&event.button.x<535) //Save button pressed TODO animation
						{
							save("savefile");
						}

						if (event.button.x>535&&event.button.x<570) //Load button pressed TODO animation
						{
							load("savefile");
						}

						if (event.button.x>600 && event.button.y>436 && event.button.x<613 && event.button.y<450) //Up layer button pressed
						{
							if (layer<9)
							{
								layer++;
								arrow_up_pressed=true;
								render();
								std::this_thread::sleep_for(std::chrono::milliseconds(200));
								render();
							}
						}

						if (event.button.x>600 && event.button.y>452 && event.button.x<613 && event.button.y<465) //Down layer button pressed
						{
							if (layer>0)
							{
								layer--;
								arrow_down_pressed=true;
								render();
								std::this_thread::sleep_for(std::chrono::milliseconds(200));
								render();
							}
						}
						render();
					}
					if (event.button.x<=625 && event.button.y>=475) //Click on coordinate pannel
					{
						if (event.button.x>=10&&event.button.x<=23&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_X++;
							render();
						}
						if (event.button.x>=30&&event.button.x<=43&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_X--;
							render();
						}
						if (event.button.x>=(int)(SCREEN_WIDTH/2-40)&&event.button.x<=(int)(SCREEN_WIDTH/2-40)+13&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_Y++;
							render();
						}
						if (event.button.x>=(int)(SCREEN_WIDTH/2-40)+20&&event.button.x<=(int)(SCREEN_WIDTH/2-40)+33&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_Y--;
							render();
						}
						if (event.button.x>=(int)(10+SCREEN_WIDTH-150)&&event.button.x<=(int)(10+SCREEN_WIDTH-150)+13&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_Z++;
							render();
						}
						if (event.button.x>=(int)(30+SCREEN_WIDTH-150)&&event.button.x<=(int)(30+SCREEN_WIDTH-150)+33&&event.button.y>=478&&event.button.y<=490) 
						{
							IN_WORLD_Z--;
							render();
						}
					}
				}

				if (event.button.button == SDL_BUTTON_RIGHT) //On right click
				{
					//std::cout<<"Right click at X:"<<event.button.x<<" Y:"<<event.button.y<<"\n";
				}
			}
		}
	}
	clean_up(); //Removes garbage
}

int Sdlinterface::minimum(int a, int b)
{
	int result=a;
	if (b<a)
	{
		result=b;
	}
	return result;
}

int Sdlinterface::maximum(int a, int b)
{
	int result=a;
	if (b>a)
	{
		result=b;
	}
	return result;
}

//Writes output to file
void Sdlinterface::writeCommandToFile(std::string filename)
{
	int x=IN_WORLD_X;
	int y=IN_WORLD_Y;
	int z=IN_WORLD_Z;
	double xf;
	double yf;
	double zf;
	std::ofstream myfile;
	myfile.open(filename.c_str());
	if (myfile.is_open()) 
	{
		for (Block* b:block_list)
		{
			xf = x+-1.5+(0.187*b->getX());
			yf = y+3.35+(-1*(0.187+0.187*b->getY()));
			zf = z-0.187*b->getZ();

			myfile<<std::fixed<<std::setprecision(3)<<"/summon armor_stand "<<xf<<"f "<<yf<<"f "<<zf<<"f {Small:1, ShowArms:1, HandItems:[{id:"<<b->getId()<<",Damage:"<<b->getDamage()<<",Count:1},{}], Pose:{RightArm:[-15f,0f,0f]}, Rotation:[45f], NoGravity:1b, Marker:1b, Invisible:1b, NoBasePlate:1f}\n";
		}
		myfile.close();
	} 
	else 
	{
	//	std::cout << "Can not open file!" << endl;
	}
}

//Loads all the resources
void Sdlinterface::load_resources()
{
	//TODO Load everything
	font = TTF_OpenFont("fonts/font.ttf",20);
}

void Sdlinterface::unload_resources()
{
	//TODO Unload everything
	//add me to clean_up
}

//Draws graphics on screen
void Sdlinterface::render()
{
	//Loads backgroung tiles
	image = load_image("interface_pngs/tile.png");
	for (int y=0; y<17; y++) 
	{
		for (int x=0; x<25; x++)
		{
			apply_surface(x*25,y*25,image, screen);
		}
	}
	//Loads bottom menu
	image = load_image("interface_pngs/bottom_menu.png");
	apply_surface(0,425,image, screen);
	//Loads coord bar 
	image = load_image("interface_pngs/coord_bar.png");
	apply_surface(0,475,image, screen);
	
	//x arrow up
	image = load_image("interface_pngs/arrow_uu.png");
	apply_surface(10,478,image, screen);
	//x arrow down
	image = load_image("interface_pngs/arrow_du.png");
	apply_surface(30,478,image, screen);
	//x sign
	textColor = {164,164,163};
	std::string s_Xs = "X: ";
	char const *text_charred_Xs = s_Xs.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Xs, textColor);
	apply_surface (55,470,message,screen);
	//x number
	textColor = {164,164,163};
	std::string s_Xn = std::to_string(IN_WORLD_X);
	char const *text_charred_Xn = s_Xn.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Xn, textColor);
	apply_surface (75,470,message,screen);
	
	//y arrow up
	image = load_image("interface_pngs/arrow_uu.png");
	apply_surface((int)(10-50+SCREEN_WIDTH/2),478,image, screen);
	//y arrow down
	image = load_image("interface_pngs/arrow_du.png");
	apply_surface((int)(30-50+SCREEN_WIDTH/2),478,image, screen);
	//y sign
	textColor = {164,164,163};
	std::string s_Ys = "Y: ";
	char const *text_charred_Ys = s_Ys.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Ys, textColor);
	apply_surface ((int)(55-50+SCREEN_WIDTH/2),470,message,screen);
	//y number
	textColor = {164,164,163};
	std::string s_Yn = std::to_string(IN_WORLD_Y);
	char const *text_charred_Yn = s_Yn.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Yn, textColor);
	apply_surface ((int)(75-50+SCREEN_WIDTH/2),470,message,screen);

	//z arrow up
	image = load_image("interface_pngs/arrow_uu.png");
	apply_surface((int)(10+SCREEN_WIDTH-150),478,image, screen);
	//z arrow down
	image = load_image("interface_pngs/arrow_du.png");
	apply_surface((int)(30+SCREEN_WIDTH-150),478,image, screen);
	//z sign
	textColor = {164,164,163};
	std::string s_Zs = "Z: ";
	char const *text_charred_Zs = s_Zs.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Zs, textColor);
	apply_surface ((int)(55+SCREEN_WIDTH-150),470,message,screen);
	//z number
	textColor = {164,164,163};
	std::string s_Zn = std::to_string(IN_WORLD_Z);
	char const *text_charred_Zn = s_Zn.c_str();
	message = TTF_RenderText_Solid(font,text_charred_Zn, textColor);
	apply_surface ((int)(75+SCREEN_WIDTH-150),470,message,screen);

	//Bottom menu arrow animation
	if (!arrow_up_pressed)
	{
		image = load_image("interface_pngs/arrow_uu.png");
		apply_surface(600,436,image, screen);
	}
	else
	{
		image = load_image("interface_pngs/arrow_up.png");
		apply_surface(600,436,image, screen);
		arrow_up_pressed=false;
	}
	if (!arrow_down_pressed)
	{
		image = load_image("interface_pngs/arrow_du.png");
		apply_surface(600,452,image, screen);
	} 
	else 
	{
		image = load_image("interface_pngs/arrow_dp.png");
		apply_surface(600,452,image, screen);
		arrow_down_pressed=false;
	}

	//Loads layer counter
	textColor = {164,164,163};
	std::string s = std::to_string(layer);
	char const *text_charred = s.c_str();
	message = TTF_RenderText_Solid(font,text_charred, textColor);
	apply_surface (585,435,message,screen);

	//Loads blocks to draw 
	for (Block* n: block_list)
	{
		if (n->getZ()==layer)
		{
			image = load_image(n->getTexture());
			apply_surface(n->getX()*25,n->getY()*25, image, screen);
		}
	}

	//Loads select point marker
	if (tile_select_point_was_set)
	{
		if (tile_select_point_Z==layer) 
		{
			image = load_image("interface_pngs/tile_select_point.png");
			apply_surface(tile_select_point_X*25,tile_select_point_Y*25, image, screen);
		}
	}

	//Loads blocks on bottom menu
	int count=0;
	for (std::string i:slots)
	{
		image = load_image(i);
		apply_surface(13+count*35,437,image, screen);
		count++;
	}

	image = load_image("interface_pngs/point_tool.png");
	apply_surface(398,434,image,screen);

	image = load_image("interface_pngs/line_tool.png");
	apply_surface(433,434,image,screen);

	image = load_image("interface_pngs/rectangle_tool.png");
	apply_surface(468,434,image,screen);

	image = load_image("interface_pngs/save.png");
	apply_surface(503,434,image,screen);

	image = load_image("interface_pngs/load.png");
	apply_surface(538,434,image,screen);
	
	//Loads block selector
	for (int i=0; i<14; i++) 
	{
		if (selector_pos==i) 
		{
			image = load_image("interface_pngs/selector.png");
			apply_surface(10+i*35,434,image, screen);
		}
	}
	
	//Loads block select menu
	if (menuopened)
	{
		image = load_image("interface_pngs/block_select_menu.png");
		apply_surface(7,5,image,screen);
		
		for (int y=0; y<(int)(all_blocks.size()/18)+1; y++)
		{
			for (int x=0; x<18; x++)
			{
				if (y*18+x<all_blocks.size())
				{
					image = load_image(all_blocks.at(y*18+x));
					apply_surface(x*32+28,32*y+25,image,screen);
				}
			}
		}
	}

	//Draws everything on screen
	SDL_Flip(screen);
}

//Saves drawn blocks to file TODO exceptions
void Sdlinterface::save(std::string filename)
{
	std::ofstream myfile;
	myfile.open(filename.c_str());
	if (myfile.is_open()) 
	{
		for (Block* b:block_list)
		{
			myfile<<b->getX()<<","<<b->getY()<<","<<b->getZ()<<","<<b->getDamage()<<","<<b->getId()<<","<<b->getTexture()<<"\n";	
		}
		myfile.close();
	} 
	else 
	{
	//	std::cout << "Can not open file!" << endl;
	}
	render();
}

//Loads block from file TODO exceptions
void Sdlinterface::load(std::string filename)
{
	std::string line;
	std::ifstream myfile;
	myfile.open(filename.c_str());
	block_list.clear();
	if (myfile.is_open()) 
	{
		int xc;
		int yc;
		int zc;
		int damage;
		std::string id;
		std::string texture;
		std::string delimiter = ",";
		size_t pos;

		while (getline(myfile,line)) 
		{
			xc = 0;
			yc = 0;
			zc = 0;
			damage = 0;
			id = "";
			texture = "";
			pos = 0;
			
			pos = line.find(delimiter);
			xc = stoi(line.substr(0,pos));
			line.erase(0,pos+delimiter.length());
			
			pos = line.find(delimiter);
			yc = stoi(line.substr(0,pos));
			line.erase(0,pos+delimiter.length());
			
			pos = line.find(delimiter);
			zc = stoi(line.substr(0,pos));
			line.erase(0,pos+delimiter.length());
			
			pos = line.find(delimiter);
			damage = stoi(line.substr(0,pos));
			line.erase(0,pos+delimiter.length());
			
			pos = line.find(delimiter);
			id = line.substr(0,pos);
			line.erase(0,pos+delimiter.length());
			
			texture = line;
			
			Block* block;
			block = new Block(xc,yc,zc,damage,id,texture);
			block_list.push_back(block);
		}
		myfile.close();
	} 
	else 
	{
		//std::cout << "The file could not be read!" << endl;
	}
	render();
}

//Loads image to draw using SDL
SDL_Surface* Sdlinterface::load_image(std::string filename)
{
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if (loadedImage != NULL)
	{
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

//Draws image using SDL
void Sdlinterface::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

//Initializes SDL
void Sdlinterface::init() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP,SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption("Microblock generator",NULL);
}

//Removes garbage
void Sdlinterface::clean_up()
{
	SDL_FreeSurface(image);
	SDL_FreeSurface(message);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

