#include "sdlinterface.h"
#include "block.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <vector>
#include <iostream>
#include <string>

Sdlinterface::Sdlinterface()
{
	bool quit = false;
	init();
	image = load_image("tile.png");
	for (int y=0; y<17; y++) 
	{
		for (int x=0; x<25; x++)
		{
			apply_surface(x*25,y*25,image, screen);
		}
	}
	image = load_image("bottom_menu.png");
	apply_surface(0,425,image, screen);
	
	std::vector<Block*> block_list = {};
	block_list.push_back(new Block(3,2,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(4,2,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(6,2,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(7,2,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(5,4,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(5,5,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(4,8,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(5,8,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(6,8,0,"cobblestone","textures/cobblestone.png"));
	block_list.push_back(new Block(2,1,0,"dirt","textures/dirt.png"));
	block_list.push_back(new Block(3,1,0,"dirt","textures/dirt.png"));
	block_list.push_back(new Block(4,1,0,"dirt","textures/dirt.png"));
	block_list.push_back(new Block(6,1,0,"dirt","textures/dirt.png"));
	block_list.push_back(new Block(7,1,0,"dirt","textures/dirt.png"));
	block_list.push_back(new Block(8,1,0,"dirt","textures/dirt.png"));
	for (Block* n: block_list)
	{
		image = load_image(n->getTexture());
		apply_surface(n->getX()*25,n->getY()*25, image, screen);
	}
	
	SDL_Flip(screen);

	while (quit == false)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
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
		optimizedImage = SDL_DisplayFormat(loadedImage);
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
	SDL_WM_SetCaption("Microblock generator",NULL);
}

void Sdlinterface::clean_up()
{
	SDL_FreeSurface(image);
	SDL_Quit();
}

