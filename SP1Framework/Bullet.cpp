#include "Bullet.h"
#include <iostream>
#include "game.h"
#include "Framework/console.h"
#include "Player.h"
using namespace std;




Bullet::Bullet(SGameChar& player, SMouseEvent& mousepos)
{
	if (player::direction == 'U')
	{

	}
	
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
