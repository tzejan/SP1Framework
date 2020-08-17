#pragma once
#include "Entity.h"
class Box :
	public Entity
{
private:
	signed char itemtag; //tag to identify what type of item the box holds
	const int amount; //Amount of items in box (constant because box will always be used in its entirety)
public:
	Box();
	~Box();
	signed char getTag();//Get itemtag
	void setTag(signed char itemtag);//Set itemtag
	int getAmt();//Get amount
};

