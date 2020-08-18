#pragma once
#include <iostream>
#include <fstream>

class Map
{
private:
	const int rowSmall, columnSmall;
	const int rowBig, columnBig;

public:
	Map();
	~Map();
	
	int getRowSmall();
	int getColumnSmall();
	int getRowBig();
	int getColumnBig();
	void chooseMap(int lvl);
	void printMap(std::fstream& level, int rows, int column);
	void printMapValues(std::fstream& level);
};

