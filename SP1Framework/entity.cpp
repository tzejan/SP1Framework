#include "Entity.h"

Entity::Entity()
{
	c.X = 0;
	c.Y = 0;
	display = ' ';
}

Entity::Entity(COORD _c, char _display)
{
	c = _c;
	display = _display;
}

Entity::Entity(int _y_pos, int _x_pos, char _display)
{
	c.Y = _y_pos;
	c.X = _x_pos;
	display = _display;

}

int Entity::get_y_pos()
{
	return c.Y;
}

COORD Entity::get_pos()
{
	return c;
}

int Entity::get_x_pos()
{
	return c.X;
}

char Entity::get_display()
{
	return display;
}

void Entity::set_display(char _display)
{
	display = _display;
}



void Entity::set_pos(COORD _c)
{
	c = _c;
}

void Entity::set_ypos(int _y_pos)
{
	c.Y = _y_pos;
}

void Entity::set_xpos(int _x_pos)
{
	c.X = _x_pos;
}

void Entity::move_up(int distance)
{
	c.Y -= distance;
}

void Entity::move_down(int distance)
{
	c.Y += distance;
}

void Entity::move_left(int distance)
{
	c.X -= distance;
}

void Entity::move_right(int distance)
{
	c.X += distance;
}
