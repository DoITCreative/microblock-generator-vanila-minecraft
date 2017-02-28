#include "SDL/SDL.h"
#include <string>
#ifndef BLOCK_H
#define BLOCK_H
class Block
{
	public:
		Block(int coord_x, int coord_y, std::string type, std::string texture_file);
		int getX();
		int getY();
		std::string getType();
		std::string getTexture();
	private:
		int coord_x;
		int coord_y;
		std::string type;
		std::string texture_file;
};
#endif
