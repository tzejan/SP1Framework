#include "guard.h"
#include "MapMaker.h"

Guard::Guard(COORD c_pos, MapMaker* map)
{
	set_pos(c_pos);
	set_display((char)2);
    entity_map = map;
}


Guard::Guard(int y_pos, int x_pos, MapMaker* map)
{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display((char)2);
    entity_map = map;
}

Guard::~Guard()
{
}


void Guard::move(int button_pressed)
{

    if (button_pressed == K_DOWN && !collide(c.X,c.Y + 1))
    {
            move_down(1);

    }
    if (button_pressed == K_LEFT && !collide(c.X - 1, c.Y))
    {
       
        move_left(1);
    }
    if (button_pressed == K_UP && !collide(c.X, c.Y - 1))
    {
        
        move_up(1);
    } 
    if (button_pressed == K_RIGHT && !collide(c.X + 1, c.Y))
    {
        move_right(1);
    }

}

bool Guard::collide(COORD entity_pos)
{
	return collide(entity_pos.X, entity_pos.Y);
	
}

bool Guard::collide(int entity_xpos, int entity_ypos)
{
    COORD pos;
    pos.X = entity_xpos;
    pos.Y = entity_ypos;
    if (entity_map->getMapArray()[entity_ypos][entity_xpos] == ' ') {
        return false;
    }
    else {
        return true;
    }
}

