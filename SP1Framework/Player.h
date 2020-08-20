#pragma once
#include "Entity.h"
#include <iostream>


class Player : public Entity
{
private:

public:
	Player(COORD c_pos);
	Player(int y_pos, int x_pos);
	~Player();
};
