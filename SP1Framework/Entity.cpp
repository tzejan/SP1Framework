#include "Entity.h"

Entity::Entity()
{
	pos.setX(0);
	pos.setY(0);
}

Entity::~Entity()
{
	//leave blank
}

Position Entity::getPos(void)
{
	return pos;
}
