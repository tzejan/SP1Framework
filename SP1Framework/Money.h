#pragma once
#include "GameObject.h"
class Money : public GameObject
{
private:
	static int totalMoney;

public:
	Money();
	virtual ~Money();

	void Interact(GameObject* obj); // Interact with object that is overlapped and ready to be execute
	bool isCollided(GameObject* obj); // Check if object is overlap with anything
	bool checkForCollision(GameObject* obj, int direction); // Check if object possible to move
	void MoveObject(int x, int y); // If money have leg to walk on his own?

	static int GetMoneyCount();
};

