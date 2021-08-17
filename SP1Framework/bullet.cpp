#include "bullet.h"

bullet::bullet()
{
	setSym(0);
	setCoordX(0);
	setCoordY(0);
	mx = 0;
	my = 0;
}

bullet::bullet(int posX, int posY,int dir)
{

	setSym(0);
	setCoordX(posX);
	setCoordY(posY);
	direection = dir;
	mx = 0;
	my = 0;
}

void bullet::movement(int dir)
{
	if (dir == 1)
	{
		setSym(124);
		//up
		setCoordY(getCoordY() - 1);
	}
	else if (dir == -1)
	{
		setSym(124);
		//down
		setCoordY(getCoordY() + 1);
	}
	else if (dir == 3)
	{
		setSym(45);
		setCoordX(getCoordX() + 1);
		//right
	}
	else if (dir == -3)
	{
		setSym(45);
		//left
		setCoordX(getCoordX() - 1);
	}
	else if (dir == 4)
	{
		setSym(47);
		//rightup
		setCoordX(getCoordX() + 1);
		setCoordY(getCoordY() - 1);
	}
	else if (dir == -4)
	{
		setSym(47);
		//leftdown
		setCoordX(getCoordX() - 1);
		setCoordY(getCoordY() + 1);
	}
	else if (dir == -2)
	{
		setSym(92);
		//leftup
		setCoordX(getCoordX() - 1);
		setCoordY(getCoordY() - 1);
	}
	else if (dir == 2)
	{
		setSym(92);
		//downright
		setCoordX(getCoordX() + 1);
		setCoordY(getCoordY() + 1);
	}
}

int bullet::GetDirection()
{
	return direection;
}



