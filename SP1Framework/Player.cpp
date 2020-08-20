#include "Player.h"

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

void Player::move()
{
    if (KeyEvent[K_UP].keyReleased)
    {
        //Beep(1440, 30);
        set_ypos(get_pos().Y - 1);
    }
    if (KeyEvent[K_LEFT].keyReleased)
    {
        //Beep(1440, 30);
        set_ypos(get_pos().X - 1);
    }
    if (KeyEvent[K_DOWN].keyReleased )
    {
        //Beep(1440, 30);
        set_ypos(get_pos().Y + 1);
    }
    if (KeyEvent[K_RIGHT].keyReleased)
    {
        //Beep(1440, 30);
        set_ypos(get_pos().X + 1);
    }

}
