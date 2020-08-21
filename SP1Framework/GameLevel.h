#pragma once
#include "MapMaker.h"

class GameLevel
{
private:
	MapMaker this_map;
	string* filename;

public:
	GameLevel();
	GameLevel(string filepath);
	~GameLevel();




};

