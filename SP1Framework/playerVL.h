#pragma once
#include "map.h"

class playerVL : public map
{
private:
	int viewRange = 0;
public:
	playerVL(int r);
	~playerVL();
	void updateVL(int x, int y);
};

