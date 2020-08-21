#include "Player.h"
<<<<<<< HEAD

=======
#include "MapMaker.h"
>>>>>>> master
Player::Player(COORD c_pos)
{
	set_pos(c_pos);
	set_display((char)1);
}

<<<<<<< HEAD
Player::Player(int y_pos, int x_pos)
=======
Player::Player(int y_pos, int x_pos) 
>>>>>>> master
{
	set_xpos(x_pos);
	set_ypos(y_pos);
	set_display((char)1);
}

Player::~Player()
{
}
<<<<<<< HEAD

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
    return false;
}

bool Player::collide(int entity_xpos, int entity_ypos)
{
    COORD entity;
    entity.X = entity_xpos;
    entity.Y = entity_ypos;

    return collide(entity);
}
=======
>>>>>>> master
