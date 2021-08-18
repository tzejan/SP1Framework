#include "bullet.h"

bullet::bullet()
{
	setSym(0);
	setCoordX(0);
	setCoordY(0);
	mx = 0;
	my = 0;
	setspeed(0.5);
}

bullet::bullet(int posX, int posY,int dir)
{

	setSym(0);
	setCoordX(posX);
	setCoordY(posY);
	direection = dir;
	mx = 0;
	my = 0;
	setspeed(0.2f);
}

void bullet::movement(int dir)
{
	if (dir == 1)
	{
		//up
		setSym(124);
		if (my > 0)
		{
			my = -1;
		}

		my -= getSpeed();
		if (ceil(my) <= -1)
		{
			setCoordY(getCoordY() - 1);
	
			my = 0;
		}
	}
	else if (dir == -1)
	{
		setSym(124);
		//down
		if (my < 0)
		{
			my = 1;
		}
		my += getSpeed();
		if (floor(my) >= 1)
		{
			//Beep(1440, 30);
			setCoordY(getCoordY() + 1);

			my = 0;
		}
	}
	else if (dir == 3)
	{
		setSym(45);
		
		//right
		if (mx < 0)
		{
			mx = 1;
		}
		mx += getSpeed();
		if (floor(mx) >= 1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() + 1);
		
			mx = 0;
		}
	}
	else if (dir == -3)
	{
		setSym(45);
		//left
		if (mx > 0)
		{
			mx = -1;
		}
		mx -= getSpeed();
		if (ceill(mx) <= -1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() - 1);
		
			mx = 0;
		}
	}
	else if (dir == 4)
	{
		setSym(47);
		//rightup
		if (mx < 0)
		{
			mx = 1;
		}
		mx += getSpeed();
		if (floor(mx) >= 1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() + 1);

			mx = 0;
		}
		setSym(124);
		if (my > 0)
		{
			my = -1;
		}

		my -= getSpeed();
		if (ceil(my) <= -1)
		{
			setCoordY(getCoordY() - 1);

			my = 0;
		}
	}
	else if (dir == -4)
	{
		setSym(47);
		//leftdown
		if (mx > 0)
		{
			mx = -1;
		}
		mx -= getSpeed();
		if (ceill(mx) <= -1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() - 1);

			mx = 0;
		}
		if (my < 0)
		{
			my = 1;
		}
		my += getSpeed();
		if (floor(my) >= 1)
		{
			//Beep(1440, 30);
			setCoordY(getCoordY() + 1);

			my = 0;
		}
	}
	else if (dir == -2)
	{
		setSym(92);
		//leftup
		if (mx > 0)
		{
			mx = -1;
		}
		mx -= getSpeed();
		if (ceill(mx) <= -1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() - 1);

			mx = 0;
		}
		setSym(124);
		if (my > 0)
		{
			my = -1;
		}

		my -= getSpeed();
		if (ceil(my) <= -1)
		{
			setCoordY(getCoordY() - 1);

			my = 0;
		}
	}
	else if (dir == 2)
	{
		setSym(92);
		//downright
		if (mx < 0)
		{
			mx = 1;
		}
		mx += getSpeed();
		if (floor(mx) >= 1)
		{
			//Beep(1440, 30);
			setCoordX(getCoordX() + 1);

			mx = 0;
		}
		if (my < 0)
		{
			my = 1;
		}
		my += getSpeed();
		if (floor(my) >= 1)
		{
			//Beep(1440, 30);
			setCoordY(getCoordY() + 1);

			my = 0;
		}
	}
}

int bullet::GetDirection()
{
	return direection;
}



