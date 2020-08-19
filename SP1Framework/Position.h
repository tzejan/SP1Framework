#pragma once
#include <stdlib.h>
#include <time.h>
#include <iostream>


#pragma once
class Position
{
private:
	int x;
	int y;
	void gotoxy(int x, int y) const;

public:
	Position();
	Position(int x, int y);
	~Position();

	int getX(void) const;
	int getY(void) const;
	void setX(int x);
	void setY(int y);
};


