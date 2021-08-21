#pragma once
#include "Entity.h"
class Rock : public Entity
{
private:
public:
	Rock(int,int);
	~Rock();
	void move(void);
	void DoMovement(int, int);
	char GetSymbol(void);
};

