#include "Box.h"

Box::Box() : itemtag{ ' ' }, amount{5}
{
}

Box::~Box()
{
}

char Box::getTag()
{
	return itemtag;
}

void Box::setTag(char itemtag)
{
	this->itemtag = itemtag;
}

int Box::getAmt()
{
	return amount;
}

void Box::setXBoxPosition(int newX)
{
	pos.setXPosition(newX);
}

void Box::setYBoxPosition(int newY)
{
	pos.setYPosition(newY);
}
