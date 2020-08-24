#pragma once
#include "Entity.h"
#include <iostream>


class Guard : public Entity
{
private:

public:
	Guard(COORD c_pos);
	Guard(int y_pos, int x_pos);
	~Guard();


	void move(int button_pressed);

	bool collide(COORD entity_pos);
	bool collide(int entity_xpos, int entity_ypos);
};
