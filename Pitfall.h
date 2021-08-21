#pragma once
#include "Entity.h"
class Pitfall :	public Entity
{
public:
	Pitfall(int,int);
	~Pitfall();
	char GetSymbol(void);
};

