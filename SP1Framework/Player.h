#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	static bool isPlayerCreate;
	static int PocketMoney;
	static bool JewelCapture;

public:
	Player();
	virtual ~Player();

	void Interact(GameObject* obj); // Interact with object that is overlapped and ready to be execute
	bool isCollided(GameObject* obj); // Check if object is overlap with anything
	bool checkForCollision(GameObject* obj, int direction); // Check if object possible to move
	void MoveObject(int x, int y); // Move player and update position

	static bool CheckOnPlayer();
	static int CheckOnMoney();
	static bool CheckOnJewel();
};

