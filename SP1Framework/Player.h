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

	void move(int button_pressed);
	bool collide(COORD entity_pos);
};
