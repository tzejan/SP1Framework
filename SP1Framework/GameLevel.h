#pragma once
#include "MapMaker.h"
#include "Entity.h"

class GameLevel
{
private:
	MapMaker this_map;
	string filename;
	Entity* map_entities;

public:
	GameLevel();
	GameLevel(string filepath);
	~GameLevel();

	//abstract functions

	//functions


};

