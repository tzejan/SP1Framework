#pragma once
#include <Windows.h>

class entity
{
protected:
	COORD Location;
	bool  m_bActive;
public:
	int getCoordX();
	int getCoordY();
	void setCoordX(int i);
	void setCoordY(int i);
	void setm_bActive(bool i);
};

