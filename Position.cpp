#include "Position.h"
#include <stdlib.h>

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;    //Overloaded constructor
	this->y = y;
}

int Position::getx() const
{
	return x;
}

int Position::gety() const
{
	return y;
}

void Position::setx(int x)
{
	if (x >= 1 && x <= 20)
	{
		this->x = x;    //Ensure x within boundaries
	}
}
 
void Position::sety(int y)
{
	if (y >= 1 && y <= 20)
	{
		this->y = y; //Ensure y within boundaries
	}
}


	
