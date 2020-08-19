#include "Collision.h"
#include "Map.h"
Col::Col()
{
}

Col::~Col()
{
}
//RETURNS WHAT IT IS COLLIDING WITH 
int Col::collidingWith(int currentY, int currentX, int moveToY, int moveToX, Map& map)
{
	return (map.getGrid( (currentY + moveToY),(currentX + moveToX) ));
}

