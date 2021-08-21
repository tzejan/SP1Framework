#include "Key.h"
#include <iostream>

Key::Key(int x, int y)
{
	this->SetEntityPosition(x, y);
}

Key::~Key()
{
}

char Key::GetSymbol(void)
{
	return 'K';
}