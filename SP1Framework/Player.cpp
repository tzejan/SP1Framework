#include "Player.h"
#include <iostream>

bool Player::isPlayerCreate = false;
int Player::PocketMoney = 0;
bool Player::JewelCapture = false;

Player::Player()
{
	isPlayerCreate = true;
	myPosition.SetMarker('N');
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

	// Remove object when interacted
	delete obj;
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
	if (myPosition.GetPosX() + 1 == obj->GetPosX() && myPosition.GetPosY() + 1 == obj->GetPosY())
		return true;
	else
		return false;
}

void Player::MoveObject(int x, int y)
{
	myPosition.UpdatePosition(x, y);
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