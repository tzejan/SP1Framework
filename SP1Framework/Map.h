#pragma once
#include <iostream>
#include <fstream>

class Map
{
private:
	int mapX, mapY;

public:
	Map();
	~Map();
	
	int getMapX();
	int getMapY();
	void setMapX(int mapX);
	void setMapY(int mapY);
};

