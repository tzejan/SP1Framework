#include "guard.h"
#include "MapMaker.h"

guard::guard(COORD c_pos)
{
	set_pos(c_pos);
	set_display('G');
}


guard::guard(int y_pos, int x_pos)
{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display((char)1);
}

guard::~guard()
{
}


void guard::move(int button_pressed)
{
}

bool guard::collide(COORD entity_pos)
{
	collide(entity_pos.X, entity_pos.Y);
	return false;
}

bool guard::collide(int entity_xpos, int entity_ypos)
{
	return false;
}

