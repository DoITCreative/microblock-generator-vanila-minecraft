#include "sdlinterface.h"
#include "block.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <iostream>
#include <string>

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
	
	image = load_image("interface_pngs/arrow_uu.png");
	apply_surface(600,436,image, screen);

	image = load_image("interface_pngs/arrow_du.png");
	apply_surface(600,452,image, screen);

	font = TTF_OpenFont("fonts/font.ttf",20);
	textColor = {164,164,163};

	std::string s = std::to_string(layer);
	char const *text_charred = s.c_str();

	message = TTF_RenderText_Solid(font,text_charred, textColor);
	apply_surface (585,435,message,screen);
	
	for (Block* n: block_list)
	{
		image = load_image(n->getTexture());
		apply_surface(n->getX()*25,n->getY()*25, image, screen);
	}
	

	int count=0;
	for (std::string i:slots)
	{
		image = load_image(i);
		apply_surface(13+count*35,437,image, screen);
		count++;
	}

	for (int i=1; i<16; i++) 
	{
		if (selector_pos==i) 
		{
			image = load_image("interface_pngs/selector.png");
			apply_surface(10+i*35,434,image, screen);
		}
	}

	SDL_Flip(screen);
}

Sdlinterface::Sdlinterface()
{
	bool quit = false;
	init();

	slots.push_back("textures/brick.png");
	slots.push_back("textures/cobblestone.png");
	slots.push_back("textures/diamond_block.png");
	slots.push_back("textures/dirt.png");
	slots.push_back("textures/glass.png");
	slots.push_back("textures/glowstone.png");
	slots.push_back("textures/gold_block.png");
	slots.push_back("textures/hay_block_side.png");
	slots.push_back("textures/ice.png");
	slots.push_back("textures/iron_block.png");
	slots.push_back("textures/log_acacia.png");
	slots.push_back("textures/log_big_oak.png");
	slots.push_back("textures/log_birch.png");
	slots.push_back("textures/log_jungle.png");
	slots.push_back("textures/log_spruce.png");
	slots.push_back("textures/planks_oak.png");
	
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
						int coord_click_x=(int)(event.button.x/25);
						int coord_click_y=(int)(event.button.y/25);
						bool isset=false;
						int counter=0;
						for (Block* b:block_list)
						{
							if (b->getX()==coord_click_x && b->getY()==coord_click_y)
							{
								block_list.erase(block_list.begin()+counter);
								counter=-1;
								delete(b);
								isset=true;
							}
							counter++;
						}

						if (!isset)
						{

							block_list.push_back(new Block(coord_click_x,coord_click_y,0,"cobblestone","textures/cobblestone.png"));
						}
						render();
					}
					//std::cout<<"Left click at X:"<<event.button.x<<" Y:"<<event.button.y<<"\n";
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

