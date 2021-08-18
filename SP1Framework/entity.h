#pragma once
#include <Windows.h>

class entity
{
private:
	COORD Location;
	char sym;
	float speed;

	//fireing
	bool  m_bActive;
	float FireRate;
	float fireCharge;

protected:
	float mx;
	float my;

public:
	int getCoordX();
	int getCoordY();
	void setCoordX(int i);
	void setCoordY(int i);
	void setm_bActive(bool i);
	bool getm_activr();
	void setSym(char a);
	char getSym();
	float getSpeed();
	void setspeed(float i);

	float getFireRate();
	void SetFireRate(float i);
	float getFireC();
	void SetFireC(float i);

	virtual void movement(int dir) = 0;
};

