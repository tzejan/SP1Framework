#pragma once
#include "game.h"
class player
{
protected:
	char direction;
public:
	SGameChar* playerptr;
	
	player(SGameChar*);
	~player();
	char GetDirection();
	void SetDirection(char dirc);



};

