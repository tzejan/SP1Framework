#pragma once
#include "Entity.h"
class Wall :public Entity
{
public:
	Wall(int,int);
	~Wall();
	char GetSymbol(void);
};

