#include "guard.h"
#include "MapMaker.h"

Guard::Guard(COORD c_pos)
{
	set_pos(c_pos);
	set_display('G');
}


Guard::Guard(int y_pos, int x_pos)
{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display((char)1);
}

Guard::~Guard()
{
}


void Guard::move(int button_pressed)
{
}

bool Guard::collide(COORD entity_pos)
{
	collide(entity_pos.X, entity_pos.Y);
	return false;
}

bool Guard::collide(int entity_xpos, int entity_ypos)
{
	return false;
}

