#include "Player.h"
#include "MapMaker.h"
Player::Player(COORD c_pos)
{
	set_pos(c_pos);
	set_display((char)1);
}

Player::Player(int y_pos, int x_pos) 
{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display((char)1);
}

Player::~Player()
{
}
