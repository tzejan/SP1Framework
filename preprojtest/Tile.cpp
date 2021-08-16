#include "Tile.h"

Tile::Tile()
{
	tile_character = ' ';
}

Tile::~Tile()
{
}

Position Tile::get_tile_pos()
{
	return tile_pos;
}

char Tile::get_tile_char()
{
	return tile_character;
}

bool Tile::get_is_wall()
{
	return (tile_character == '#') ? (true) : (false);
}

bool Tile::get_is_occupied()
{
	return (tile_character == ' ') ? false : true;
}

void Tile::set_tile_char(char c)
{
	tile_character = c;
}
