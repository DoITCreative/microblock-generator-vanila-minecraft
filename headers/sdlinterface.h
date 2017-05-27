#include <string>
#include <vector>
#include "block.h"
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
		const int SCREEN_HEIGHT = 500; 
		const int SCREEN_BPP = 32;	
		int IN_WORLD_X = 0;
		int IN_WORLD_Y = 0;
		int IN_WORLD_Z = 0;
		SDL_Surface* image = NULL;
		SDL_Surface* screen = NULL;
		SDL_Surface* message = NULL;
		TTF_Font* font = NULL;
		SDL_Color textColor = {255,255,255};
		SDL_Event event;
		int layer = 0;
		bool menuopened;
		bool arrow_up_pressed=false;
		bool arrow_down_pressed=false;
		int selector_pos = 0;
		std::vector<Block*> block_list = {};
		std::vector<std::string> slots = {};
		std::vector<std::string> ids = {};
		std::vector<std::string> all_ids = {};
		std::vector<int> damage = {};
		std::vector<int> all_damage = {};
		std::vector<std::string> all_blocks = {};
	private:
		SDL_Surface* load_image(std::string filename);
		void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
		void init();
		int minimum(int a, int b);
		int maximum(int a, int b);
		void clean_up();
		void render();
		void save(std::string filename);
		void load(std::string filename);
		void writeCommandToFile(std::string filename);
};

#endif
