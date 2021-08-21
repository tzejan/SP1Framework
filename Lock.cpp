#include "Lock.h"
#include<iostream>

Lock::Lock(int x, int y)
{
	this->SetEntityPosition(x, y);
}

Lock::~Lock()
{
}

char Lock::GetSymbol(void)
{
	return 'L';
}