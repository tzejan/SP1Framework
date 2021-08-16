#pragma once
#include <bits/stdc++.h>
#include "Tile.h"
#include "Test_character.h"
class Grid
{
private:
	Tile grid_map[15][35];
	std::bitset<4> door_config;
	std::string name;
	std::string room_pos;
public:
	Grid();
	~Grid();

	//getters
	std::string get_name();
	std::string get_room_pos();
	Tile get_tile(int x, int y);
	int get_door_config(int i);
	void print_row(int i);

	//setters
	void set_name(std::string s);
	void set_door_config(int i);
	void set_door_config();
	void set_room_pos(std::string s);

	//others
	void update_door_pos();
	void import_grid(std::string file_name);
};

