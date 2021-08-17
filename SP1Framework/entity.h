#pragma once
#include <Windows.h>

class entity
{
private:
	COORD Location;
	bool  m_bActive;
	char sym;
	float speed;

protected:
	float mx;
	float my;

public:
	int getCoordX();
	int getCoordY();
	void setCoordX(int i);
	void setCoordY(int i);
	void setm_bActive(bool i);
	void setSym(char a);
	char getSym();
	float getSpeed();
	void setspeed(float i);

	virtual void movement(int dir) = 0;
};

