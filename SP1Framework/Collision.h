#pragma once
#include "Map.h"

class Col
{
public:
	Col();
	~Col();

	int collidingWith(int currentY, int currentX, int moveToY, int moveToX, Map& map);
};