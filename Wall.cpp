#include "Wall.h"
Wall::Wall(int x,int y)
{
	this->SetEntityPosition(x, y);
}
Wall::~Wall()
{
}

char Wall::GetSymbol(void)
{
	return 'W';
}

