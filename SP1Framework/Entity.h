#pragma once
#include "Position.h"
class Entity
{
private:
	Position pos;

public:
	Entity();
	virtual ~Entity();
	Position getPos(void);
};

