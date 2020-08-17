#include "Box.h"

Box::Box() : itemtag{ ' ' }, amount{5}
{
}

Box::~Box()
{
}

signed char Box::getTag()
{
	return itemtag;
}

void Box::setTag(signed char itemtag)
{
	this->itemtag = itemtag;
}

int Box::getAmt()
{
	return amount;
}
