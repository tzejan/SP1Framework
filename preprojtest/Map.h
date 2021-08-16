#pragma once
#include <bits/stdc++.h>
#include "Grid.h"
class Map
{
private:
	char minmap[4][4];
	Grid level_map[4][4];
	bool is_stolen;
public:
	Map();
	~Map();

	//getters
	char get_minmap_char(int x, int y);
	Grid get_map_grid(int x, int y);

	//setters
	void update_minmap_char(std::string room_number);
};

