#pragma once
#include "Entity.h"
class Box: 
	private Entity
{
private:
	char itemtag; //tag to identify what type of item the box holds
	const int amount; //Amount of items in box (constant because box will always be used in its entirety)
public:
	Box();
	~Box();
	char getTag();//Get itemtag
	void setTag(char itemtag);//Set itemtag
	int getAmt();//Get amount
	void setXBoxPosition(int newX);
	void setYBoxPosition(int newY);
};

