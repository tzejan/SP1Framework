#include "Player.h"

#include "MapMaker.h"



Player::Player(COORD c_pos, MapMaker* map)
{
	set_pos(c_pos);
	set_display('@');
    entity_map = map;
}

Player::Player(int y_pos, int x_pos, MapMaker* map)

{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display('@');
    entity_map = map;
}

Player::~Player()
{
}


void Player::move(int button_pressed)
{
    if (button_pressed == K_DOWN && !collide(c.X, c.Y + 1))
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

bool Player::collide(COORD entity_pos)
{
    return collide(entity_pos.X, entity_pos.Y);
    
}

bool Player::collide(int entity_xpos, int entity_ypos)
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
