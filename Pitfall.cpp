#include "Pitfall.h"

Pitfall::Pitfall(int x,int y)
{
	this->SetEntityPosition(x, y);
}
Pitfall::~Pitfall()
{
}

char Pitfall::GetSymbol(void)
{
	return '0';
}
