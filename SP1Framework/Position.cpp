#include "Position.h"
#include <iostream>

Position::Position()
{
	PosX = 0;
	PosY = 0;
	markLabel = '?';
}

Position::~Position()
{
	std::cout << "Position have been removed from GameObject!" << std::endl;
}

void Position::UpdatePosition(int x, int y, bool set)
{
	if (set)
	{
		PosX = x;
		PosY = y;
	}
	else
	{
		PosX += x;
		PosY += y;
	}
}

void Position::SetMarker(char m)
{
	markLabel = m;
}

const int Position::GetPosX()
{
	return PosX;
}

const int Position::GetPosY()
{
	return PosY;
}

const char Position::GetMarker()
{
	return markLabel;
}