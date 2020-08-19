#pragma once
#include <iostream>
#include <fstream>
#include "Framework\console.h"

class Map
{
private:
	int mapArray[25][80];

public:
	Map();
	~Map();
	
	int getGrid(int y, int x);
	void setGrid(int y, int x, int number);
	void chooseMap(int lvl, Console& console);
	void printMap(std::fstream& level, Console& console);
};

