#include "Money.h"
#include <iostream>

int Money::totalMoney = 0;

Money::Money()
{
	totalMoney++;
	myPosition.UpdatePosition(rand() % 50 + 0, rand() % 24 + 0, true);
	myPosition.SetMarker('M');

	std::cout << "Money have been placed!" << std::endl;
}

Money::~Money()
{
	totalMoney--;
	std::cout << "Money have been taken by someone else!" << std::endl;
}

void Money::Interact(GameObject* obj) 
{
	delete this;
}

bool Money::isCollided(GameObject* obj)
{
	if (myPosition.GetPosX() == obj->GetPosX() && myPosition.GetPosY() == obj->GetPosY())
		return true;
	else
		return false;
}

bool Money::checkForCollision(GameObject* obj, int direction)
{
	return false;
}

void Money::MoveObject(int x, int y)
{
	// ??? No move function ???
}

int Money::GetMoneyCount()
{
	return totalMoney;
}