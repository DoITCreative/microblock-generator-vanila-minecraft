#include "SDL/SDL.h"
#include <string>
#ifndef BLOCK_H
#define BLOCK_H
class Block
{
	public:
		Block(int coord_x, int coord_y, int coord_z, int damage, std::string id, std::string texture_file);
		~Block();
		int getX();
		int getY();
		int getZ();
		int getDamage();
		std::string getId();
		std::string getTexture();
	private:
		int coord_x;
		int coord_y;
		int coord_z;
		int damage;
		std::string id;
		std::string texture_file;
};
#endif
