#include "Position.h"

Position::Position()
{
	PosX = 0;
	PosY = 0;
	markLabel = '?';
}

Position::~Position()
{
	// Remove Position
}

void Position::UpdatePosition(int x, int y)
{
	PosX += x;
	PosY += y;
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