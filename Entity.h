#pragma once
#include "Position.h"
class Entity //Abstract class
{
protected:
	Position EntityPosition;
public:
	virtual void move(void);
	virtual void DoMovement(int,int);
	virtual char GetSymbol(void) = 0;
	virtual ~Entity(); //virtual destructor
	Position GetEntityPosition(void)const;   //return entity position
	void SetEntityPosition(int x, int y);  //Set entity new position
	bool isVirtualKeyPressed(int);
	

};

