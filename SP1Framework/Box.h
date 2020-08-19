#pragma once
#include "Entity.h"
#include "Framework\console.h"
#include "game.h"

class Box :
	public Entity
{
private:
	int itemtag; //tag to identify what type of item the box holds
	const int amount; //Amount of items in box (constant because box will always be used in its entirety)

public:
	Box();
	~Box();
	int getTag();//Get itemtag
	void setTag(int itemtag);//Set itemtag
	int getAmt();//Get amount

	

};

