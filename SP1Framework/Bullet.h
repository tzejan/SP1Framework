#pragma once
#include "game.h"
#include "Framework/console.h"
class Bullet 
{
public:
	int x, y;

	char direction;

	Bullet(SGameChar& player, char direction);
	~Bullet();
	

	void  UpdateXandY(Console& console);
};

