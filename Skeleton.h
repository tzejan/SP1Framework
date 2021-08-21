#pragma once
#include "Entity.h"
class Skeleton :public Entity
{
public:
	Skeleton(int, int);
	~Skeleton();
	char GetSymbol(void);
	void move(void);
	void DoMovement(int, int);
};

