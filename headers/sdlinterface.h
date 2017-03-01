#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#ifndef SDLINTERFACE_H
#define SDLINTERFACE_H
class Sdlinterface 
{
	public:
		Sdlinterface();
	protected:
		//The attributes of the screen 
		const int SCREEN_WIDTH = 625; 
		const int SCREEN_HEIGHT = 475; 
		const int SCREEN_BPP = 32;	
		SDL_Surface* image = NULL;
		SDL_Surface* screen = NULL;
		SDL_Surface* message = NULL;
		TTF_Font* font = NULL;
		SDL_Color textColor = {255,255,255};
		SDL_Event event;
		int layer = 0;
		int selector_pos = 1;

	private:
		SDL_Surface* load_image(std::string filename);
		void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
		void init();
		void clean_up();

};

#endif
