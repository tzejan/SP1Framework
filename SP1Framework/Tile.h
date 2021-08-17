#pragma once
#include "Position.h"
#include "Framework/console.h"
class Tile
{
private:
	char tileCharacter;
	Position tilePos;
	bool canBeSeen;
	WORD tile_color;
public:
	//CONSTRUCTORS AND DESTRUCTORS
	Tile();
	~Tile();

	//GETTERS
	Position get_tile_pos();
	char get_tile_char();
	bool get_is_wall();
	bool get_is_occupied();
	WORD get_tile_color();
	bool get_can_be_seen();

	//SETTERS
	void set_tile_char(char c);
	void set_tile_color(WORD char_attribute);
	void set_canBeSeen(bool b);

	//others
	void set_tile_color();
};
