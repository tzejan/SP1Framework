#pragma once
#include "game.h"
#include "Framework/console.h"
class Bullet 
{
public:
	int x, y;
	int goal_x, goal_y;
	int gradient;
	int c;

	Bullet(SGameChar& player, SMouseEvent& mousepos);
	~Bullet();
	

	void  UpdateXandY(Console& console);
};

