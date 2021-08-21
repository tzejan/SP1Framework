#include "Entity.h"
#include <iostream>
#include "Position.h"
#include <Windows.h>


void Entity::move(void)
{
	std::cout << "Move";
}
void Entity::DoMovement(int,int)
{
	std::cout << "Move";
}
Entity::~Entity()
{
}
Position Entity::GetEntityPosition(void) const
{
	return EntityPosition;
}

void Entity::SetEntityPosition(int x, int y)
{
	this->EntityPosition.setx(x);   //Set new position
	this->EntityPosition.sety(y);
}
bool Entity::isVirtualKeyPressed(int virKey)
{
	return GetAsyncKeyState(virKey) & 0x80000; // GetAsyncKeyState GetKeyState
}

