#pragma once
#include <iostream>
#include <fstream>
#include "Framework\console.h"

class Map
{
private:
	const int row, column;

public:
	Map();
	~Map();
	
	int getRow();
	int getColumn();
	void chooseMap(int lvl, Console& console);
	void printMap(std::fstream& level, int rows, int column, Console& console);
};

