#include "GameObject.h"
#include <iostream>

GameObject::~GameObject()
{
	std::cout << "GameObject have been removed!" << std::endl;
}

const int GameObject::GetPosX()
{
	return myPosition.GetPosX();
}

const int GameObject::GetPosY()
{
	return myPosition.GetPosY();
}

const char GameObject::GetMarker()
{
	return myPosition.GetMarker();
}