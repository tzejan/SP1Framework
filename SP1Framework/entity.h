#pragma once
#include <Windows.h>

class entity
{
protected:
	COORD Location;
	bool  m_bActive;
	char sym;
public:
	int getCoordX();
	int getCoordY();
	void setCoordX(int i);
	void setCoordY(int i);
	void setm_bActive(bool i);
	void setSym(char a);
	char getSym();
};

