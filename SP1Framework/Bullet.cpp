#include "Bullet.h"
#include <iostream>
#include "game.h"
#include "Framework/console.h"
using namespace std;




Bullet::Bullet(SGameChar& player, SMouseEvent& mousepos)
{
	x = player.m_cLocation.X;
	y = player.m_cLocation.Y;

	goal_x = mousepos.mousePosition.X;
	goal_y = mousepos.mousePosition.Y;

	gradient = (goal_y - y) / (goal_x - x);
	c = y - (gradient * x);
	
}

Bullet::~Bullet()
{

}

void Bullet::UpdateXandY(Console& console)
{

	x++;
	y = (gradient * x) + c;
	gotoXY(x, y);
	COORD c;
	c.X = x;
	c.Y = y;
	console.writeToBuffer(c, "*", 0x3D);
	
}
