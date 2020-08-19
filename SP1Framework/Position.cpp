#include "Position.h"
#include <Windows.h>

void Position::gotoxy(int x, int y) const
{
	COORD scrn;
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	scrn.X = x;
	scrn.Y = y;
	SetConsoleCursorPosition(hConsoleOutput, scrn);
}

Position::Position()
{
	x = 0;
	y = 0;
}

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}

Position::~Position()
{
	//intentionally left blank
}

int Position::getX(void) const
{
	return x;
}

int Position::getY(void) const
{
	return y;
}

void Position::setX(int x)
{
	this->x = x;
}

void Position::setY(int y)
{
	this->y = y;
}

