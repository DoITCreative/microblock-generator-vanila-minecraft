#include "sdlinterface.h"
#include "block.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <vector>
#include <iostream>
#include <string>

Sdlinterface::Sdlinterface()
{
	bool quit = false;
	init();
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
	
	
	for (int i=0; i<16; i++) 
	{
		if (selector_pos==i) 
		{
			image = load_image("interface_pngs/selector.png");
			apply_surface(10+i*35,434,image, screen);
		}
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

