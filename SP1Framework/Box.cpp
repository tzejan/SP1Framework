#include "Box.h"

Box::Box() : itemtag{ ' ' }, amount{5}
{
}

Box::~Box()
{
}

int Box::getTag()
{
	return itemtag;
}

void Box::setTag(int itemtag)
{
	this->itemtag = itemtag;
}

int Box::getAmt()
{
	return amount;
}
