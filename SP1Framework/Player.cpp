#include "Player.h"

Player::Player()
{
	setSym(0);
	setCoordX(0);
	setCoordY(0);
	SetFireRate(1);
	setm_bActive(true);
	SetFireC(0);
	mx = 0;
	my = 0;
}

void Player::movement(int dir)
{
	
	if (dir == 1)
	{
		if (my > 0)
		{
			my = -1;
		}

		my -= getSpeed();
		if (ceil(my) <= -1)
		{
			setCoordY(getCoordY() - 1);
			setSym(94);
			my = 0;
		}
	}
	if (dir == 2)
	{
		if (my < 0)
		{
			my = 1;
		}
		my += getSpeed();
		if (floor(my) >= 1)
		{
			//Beep(1440, 30);
			setCoordY(getCoordY() + 1);
			setSym(118);
			my = 0;
		}
	}
	if (dir == 3)
	{
		if (mx > 0)
		{
			mx = -1;
		}
		mx -= getSpeed();
		if (ceill(mx) <= -1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() - 1);
			setSym(60);
			mx = 0;
		}
	}
	if (dir == 4)
	{
		if (mx < 0)
		{
			mx = 1;
		}
		mx += getSpeed();
		if (floor(mx) >= 1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() + 1);
			setSym(62);
			mx = 0;
		}
	}
}

void Player::setHp(int h)
{
	hp = h;
}

int Player::getHp()
{
	return hp;
}


