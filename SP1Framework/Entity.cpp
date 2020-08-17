#include "Entity.h"

Entity::Entity()
{
	pos.setXPosition(0);
	pos.setYPosition(0);
}

Entity::~Entity()
{
	//leave blank
}

Position Entity::getPos(void)
{
	return Position();
}
