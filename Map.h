#pragma once
#include "Entity.h"
using namespace std;

class game_map
{
private:
	Entity* coordinate[20][20];
public:
	game_map();
	void printmap();
	void set(int y, int x, Entity* e);
	Entity* get_coordinate(int row, int col);


};