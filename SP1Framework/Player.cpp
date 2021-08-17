#include "Player.h"
#include <iostream>

bool Player::isPlayerCreate = false;
int Player::PocketMoney = 0;
bool Player::JewelCapture = false;

Player::Player()
{
	isPlayerCreate = true;
	myPosition.SetMarker('P');
	myPosition.UpdatePosition(10, 10, true);

	std::cout << "Player have been created!" << std::endl;
}

Player::~Player()
{
	isPlayerCreate = false;
	std::cout << "Player have been destroyed!" << std::endl;
}

void Player::Interact(GameObject* obj)
{
	switch (obj->GetMarker())
	{
		case 'M':
			PocketMoney++; // Default amount by 1
			break;

		case 'J':
			JewelCapture = true; // Player got the jewel
			break;
	}
}

bool Player::isCollided(GameObject* obj)
{
	if (myPosition.GetPosX() == obj->GetPosX() && myPosition.GetPosY() == obj->GetPosY())
		return true;
	else 
		return false;
}

bool Player::checkForCollision(GameObject* obj, int direction) 
{
	switch (direction)
	{
		case 1: // UP
			if (myPosition.GetPosX() == obj->GetPosX() && myPosition.GetPosY() - 1 == obj->GetPosY())
				return true;

		case 2: // LEFT
			if (myPosition.GetPosX() - 1 == obj->GetPosX() && myPosition.GetPosY() == obj->GetPosY())
				return true;

		case 3: // DOWN
			if (myPosition.GetPosX() == obj->GetPosX() && myPosition.GetPosY() + 1 == obj->GetPosY())
				return true;

		case 4: // RIGHT
			if (myPosition.GetPosX() + 1 == obj->GetPosX() && myPosition.GetPosY() == obj->GetPosY())
				return true;

		default: // STOP
			break;
	}

	// If there is no collision
	return false;
}

void Player::MoveObject(int x, int y)
{
	myPosition.UpdatePosition(x, y, false);
}

bool Player::CheckOnPlayer()
{
	return isPlayerCreate;
}

int Player::CheckOnMoney()
{
	return PocketMoney;
}

bool Player::CheckOnJewel()
{
	return JewelCapture;
}