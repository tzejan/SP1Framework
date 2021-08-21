#pragma once
#include "Entity.h"
class Player :  public Entity
{
private:
	bool HaveKey;
	static int direction;
	static int Moves;
public:
	Player(int,int);
	~Player();
	void move(void);
	void DoMovement(int,int);
	char GetSymbol(void);
	void SetHaveKey(bool);
	bool GetHaveKey(void);
	static void SetPlayerDirection(int);
	static int GetPlayerDirection(void);
	static void MovesDecreaseByOne(void);
	static void SetMoves(int);
	static int GetMoves(void);
};

