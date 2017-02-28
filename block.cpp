#include "block.h"
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

Block::Block(int coord_x, int coord_y, std::string type, std::string texture_file) 
{
	this->coord_x=coord_x;	
	this->coord_y=coord_y;	
	this->type=type;	
	this->texture_file=texture_file;	
}

int Block::getX()
{
	return this->coord_x;
}

int Block::getY()
{
	return this->coord_y;
}

std::string Block::getType()
{
	return this->type;
}

std::string Block::getTexture()
{
	return this->texture_file;
}

