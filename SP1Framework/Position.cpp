#include "Position.h"

Position::Position()
{
	x = -1;
	y = -1;
}

Position::~Position()
{

}

void Position::setXpos(int Xpos)
{
	Xpos = x;
}

int Position::getXpos()
{
	return x;
}

void Position::setYpos(int Ypos)
{
	Ypos = y;
}

int Position::getYpos()
{
	return y;
}