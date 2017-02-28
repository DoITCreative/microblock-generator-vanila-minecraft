#include <string>
#include "SDL/SDL.h"
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
		SDL_Event event;

	private:
		SDL_Surface* load_image(std::string filename);
		void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
		void init();
		void load_files();
		void clean_up();

};

#endif
