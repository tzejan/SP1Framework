#include "Bullet.h"
#include <iostream>
#include "game.h"
#include "Framework/console.h"
#include "Player.h"
using namespace std;




Bullet::Bullet(SGameChar& player, char direction)
{
	this->direction = direction;

	
}

Bullet::~Bullet()
{

}

void Bullet::UpdateXandY(Console& console)
{

	if (direction == 'U')
	{
		y -= 1;
	}
	if (direction == 'D')
	{
		y += 1;
	}
	if (direction == 'L')
	{
		x -= 1;
	}
	if (direction == 'R')
	{
		x += 1;
	}
	
}
