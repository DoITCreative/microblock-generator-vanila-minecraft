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

void Sdlinterface::render()
{
	image = load_image("interface_pngs/tile.png");
	for (int y=0; y<17; y++) 
	{
		for (int x=0; x<25; x++)
		{
			apply_surface(x*25,y*25,image, screen);
		}
	}
	image = load_image("interface_pngs/bottom_menu.png");
	apply_surface(0,425,image, screen);
	
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

	font = TTF_OpenFont("fonts/font.ttf",20);
	textColor = {164,164,163};

	std::string s = std::to_string(layer);
	char const *text_charred = s.c_str();

	message = TTF_RenderText_Solid(font,text_charred, textColor);
	apply_surface (585,435,message,screen);
	
	for (Block* n: block_list)
	{
		if (n->getZ()==layer)
		{
			image = load_image(n->getTexture());
			apply_surface(n->getX()*25,n->getY()*25, image, screen);
		}
	}

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

	for (int i=0; i<14; i++) 
	{
		if (selector_pos==i) 
		{
			image = load_image("interface_pngs/selector.png");
			apply_surface(10+i*35,434,image, screen);
		}
	}

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
	SDL_Flip(screen);
}

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


Sdlinterface::Sdlinterface()
{
	bool quit = false;
	menuopened=false;
	init();

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

	all_blocks.push_back("textures/brick.png");
	all_blocks.push_back("textures/cobblestone.png");
	all_blocks.push_back("textures/diamond_block.png");
	all_blocks.push_back("textures/dirt.png");
	all_blocks.push_back("textures/glass.png");
	all_blocks.push_back("textures/glowstone.png");
	all_blocks.push_back("textures/gold_block.png");
	all_blocks.push_back("textures/hay_block_side.png");
	all_blocks.push_back("textures/iron_block.png");
	all_blocks.push_back("textures/log_acacia.png");
	all_blocks.push_back("textures/log_birch.png");
	all_blocks.push_back("textures/log_jungle.png");
	all_blocks.push_back("textures/log_spruce.png");
	all_blocks.push_back("textures/planks_oak.png");
	for (int i=0; i<202; i++) // 216 for 1
	{
		all_blocks.push_back("textures/planks_oak.png");
	}

	render();
	while (quit == false)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				for (Block* b:block_list)
				{
					delete(b);
				}
				quit = true;
			}

			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					if (event.button.x<=625 && event.button.y<=425)
					{
						if (menuopened) 
						{
							if (event.button.x>28 && event.button.x<595 && event.button.y>25 && event.button.y<400)
							{
								int xclick=(int)((event.button.x-28)/32);
								int yclick=(int)((event.button.y-25)/32);
								slots.at(selector_pos)=all_blocks.at(yclick*18+xclick);
								menuopened=false;
								render();
							}
						}
						else
						{
							int coord_click_x=(int)(event.button.x/25);
							int coord_click_y=(int)(event.button.y/25);
							bool isset=false;
							int counter=0;
							for (Block* b:block_list)
							{
								if (b->getX()==coord_click_x && b->getY()==coord_click_y && b->getZ()==layer)
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
								switch (selector_pos)
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
					if (event.button.x<=625 && event.button.y>425)
					{
						if (event.button.x<500)
						{
							if(selector_pos!=(int)((event.button.x-10)/35))
							{
								selector_pos=(int)((event.button.x-10)/35);
							}
							else
							{
								//Open menu to select block
								blockselect();	
							}
								
						}

						if (event.button.x>500&&event.button.x<535)
						{
							save("savefile");
						}

						if (event.button.x>535&&event.button.x<570)
						{
							load("savefile");
						}

						if (event.button.x>600 && event.button.y>436 && event.button.x<613 && event.button.y<450)
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

						if (event.button.x>600 && event.button.y>452 && event.button.x<613 && event.button.y<465)
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

				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					//std::cout<<"Right click at X:"<<event.button.x<<" Y:"<<event.button.y<<"\n";
				}
			}
		}
	}
	clean_up();
}

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

void Sdlinterface::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	SDL_Rect offset;
	offset.x=x;
	offset.y=y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void Sdlinterface::init() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT, SCREEN_BPP,SDL_SWSURFACE);
	TTF_Init();
	SDL_WM_SetCaption("Microblock generator",NULL);
}

void Sdlinterface::clean_up()
{
	SDL_FreeSurface(image);
	SDL_FreeSurface(message);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void Sdlinterface::blockselect()
{
	if (menuopened)
	{
		menuopened=false;
		render();
	}
	else
	{
		menuopened=true;
	}
}

