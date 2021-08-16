#pragma once
#include "Position.h"
class Tile
{
private:
	char tile_character;
	Position tile_pos;
public:
	//CONSTRUCTORS AND DESTRUCTORS
	Tile();
	~Tile();

	//GETTERS
	Position get_tile_pos();
	char get_tile_char();
	bool get_is_wall();
	bool get_is_occupied();

	//SETTERS
	void set_tile_char(char c);
};

