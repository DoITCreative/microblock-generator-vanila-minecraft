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
	slots.push_back("textures/log_jungle.png");
	slots.push_back("textures/log_spruce.png");
	slots.push_back("textures/planks_oak.png");

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
	all_blocks.push_back("textures/redstone_lamp_on.png");
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
	all_blocks.push_back("textures/stone_slab_side.png");
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

	// Fills rest of space with garbage blocks
	for (int i=0; i<81; i++) // 216 for 1
	{
		all_blocks.push_back("textures/planks_oak.png");
	}
	

	render(); //Redraws screen
	while (quit == false)
	{
		while (SDL_PollEvent(&event)) //Checks events
		{
			if (event.type == SDL_QUIT) //On "x"(Quit) button pressed
			{
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
								slots.at(selector_pos)=all_blocks.at(yclick*18+xclick); //Changes picture on bottom pannel, where sector points
								menuopened=false;
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
								switch (selector_pos) //Places block from selector to the grid
								{
									case 0:
										b = new Block(coord_click_x,coord_click_y,layer,0,"brick",slots.at(0)); //TODO ids
										break;
									case 1:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(1));
										break;
									case 2:
										b = new Block(coord_click_x,coord_click_y,layer,0,"diamond_block",slots.at(2));
										break;
									case 3:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(3));
										break;
									case 4:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(4));
										break;
									case 5:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(5));
										break;
									case 6:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(6));
										break;
									case 7:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(7));
										break;
									case 8:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(8));
										break;
									case 9:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(9));
										break;
									case 10:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(10));
										break;
									case 11:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(11));
										break;
									case 12:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(12));
										break;
									case 13:
										b = new Block(coord_click_x,coord_click_y,layer,0,"cobblestone",slots.at(13));
										break;
								}
								block_list.push_back(b);
							}
							render();
						}
					}
					if (event.button.x<=625 && event.button.y>425) //If bottom menu is clicked
					{
						if (event.button.x<500) //Clicked on block in bottom menu
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
	font = TTF_OpenFont("fonts/font.ttf",20);
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

	//Loads blocks on bottom menu
	int count=0;
	for (std::string i:slots)
	{
		image = load_image(i);
		apply_surface(13+count*35,437,image, screen);
		count++;
	}

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
	
	//Loads block select menu    TODO check y
	if (menuopened)
	{
		image = load_image("interface_pngs/block_select_menu.png");
		apply_surface(7,5,image,screen);

		for (int y=0; y<(int)(all_blocks.size()/18); y++)
		{
			for (int x=0; x<18; x++)
			{
				image = load_image(all_blocks.at(y*18+x));
				apply_surface(x*32+28,32*y+25,image,screen);
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

