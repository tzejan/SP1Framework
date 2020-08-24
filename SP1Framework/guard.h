#pragma once
#include "Entity.h"
#include <iostream>


class guard : public Entity
{
private:

public:
	guard(COORD c_pos);
	guard(int y_pos, int x_pos);
	~guard();


	void move(int button_pressed);

	bool collide(COORD entity_pos);
	bool collide(int entity_xpos, int entity_ypos);
};
