#include "Position.h"

position::position(): x(-99), y(-99)
{
}

position::position(int x, int y): x(x), y(y)
{  
}

position::~position()
{
	//left blank intentionally
}

int position::GetXY(char xy)
{
	if (xy == 'x')
	{
		return x;
	}
	else if (xy =='y')
	{
		return y;
	}
}

void position::SetXY(char xy, int value)
{
	if (xy == 'x')
	{
		x = value;
	}
	else if (xy == 'y')
	{
		y = value;
	}
}
