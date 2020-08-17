#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

class Position
{
private:
	int* x;
	int* y;

public:
	Position();
	~Position();

	void setXPosition(int newX);
	void setYPosition(int newY);

	int getXPosition();
	int getYPosition();

	bool isCoordinatesAlreadyUsed(std::vector<Position> currentList);
	void generateRandomMapCoordinates();
};


