#pragma once
#include"Entity.h"
#include<iostream>

class Lock : public Entity
{
public:
	Lock(int, int);
	~Lock();
	char GetSymbol(void);
};