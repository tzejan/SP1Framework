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

void Player::move(int button_pressed)
{
    //if (!collide(this->get_pos())) {
        if (button_pressed == K_UP)
        {
            //Beep(1440, 30);
            set_ypos(get_pos().Y - 1);
        }
        if (button_pressed == K_LEFT)
        {
            //Beep(1440, 30);
            set_xpos(get_pos().X - 1);
        }
        if (button_pressed == K_DOWN)
        {
            //Beep(1440, 30);
            set_ypos(get_pos().Y + 1);
        }
        if (button_pressed ==  K_RIGHT)
        {
            //Beep(1440, 30);
            set_xpos(get_pos().X + 1);
        }
    //}
}

bool Player::collide(COORD entity_pos)
{
    collide(entity_pos.X, entity_pos.Y);
    return false;
}

