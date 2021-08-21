#pragma once
#include "Entity.h"
class Key : public Entity
{
public:
	Key(int, int);
	~Key();
	char GetSymbol(void);
};