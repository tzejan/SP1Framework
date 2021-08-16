#include "Grid.h"

Grid::Grid() : room_pos("--"), name("")
{
	for (int j = 0; j < 15; j++) {
		for (int i = 0; i < 35; i++) {
			grid_map[j][i].get_tile_pos().set_coordinates(j, i);
			grid_map[j][i].set_tile_char('#');
		}
	}
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			grid_map[2 + i][7 + j].set_tile_char(' ');
		}
	}
}

Grid::~Grid()
{
}

std::string Grid::get_name()
{
	return name;
}

std::string Grid::get_room_pos()
{
	return room_pos;
}

Tile Grid::get_tile(int x, int y)
{
	return grid_map[y][x];
}

int Grid::get_door_config(int i)
{
	return door_config[i];
}

void Grid::print_row(int i)
{
	for (int j = 0; j < 35; j++) {
		std::cout << grid_map[i][j].get_tile_char();
	}
}

void Grid::set_name(std::string s)
{
	name = s;
}

void Grid::set_door_config(int i)
{
	door_config.set(i);
}

void Grid::set_door_config()
{
	//sets bitset to 1111
	door_config.set();
	//changes some of the bits to 0
	if (room_pos[0] == '0') {
		door_config.reset(0);
	}
	if (room_pos[0] == '3') {
		door_config.reset(1);
	}
	if (room_pos[1] == '0') {
		door_config.reset(2);
	}
	if (room_pos[1] == '3') {
		door_config.reset(3);
	}
}

void Grid::set_room_pos(std::string s)
{
	room_pos = s;
}

void Grid::update_door_pos()
{
	//top door
	if (door_config[0] == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				grid_map[j][15 + i].set_tile_char(' ');
			}
		}
	}
	//bottom door
	if (door_config[1] == 1) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 2; j++) {
				grid_map[13 + j][15 + i].set_tile_char(' ');
			}
		}
	}
	//left door
	if (door_config[2] == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				grid_map[i + 6][j].set_tile_char(' ');
			}
		}
	}
	//right door
	if (door_config[3] == 1) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 7; j++) {
				grid_map[i + 6][j + 28].set_tile_char(' ');
			}
		}
	}
}

void Grid::import_grid(std::string file_name)
{
	std::ifstream readfile (file_name);
	std::getline(readfile, name);
	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 21; j++) {
			char c;
			readfile >> c;
			(c != '?') ? (grid_map[2 + i][7 + j].set_tile_char(c)) : (grid_map[2 + i][7 + j].set_tile_char(' '));

		}
	}
	readfile.close();
}