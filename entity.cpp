#include "Entity.h"

Entity::Entity(int _y_pos, int _x_pos, char _display)
{
	y_pos = _y_pos;
	x_pos = _x_pos;
	display = _display;

}

int Entity::get_y_pos()
{
	return y_pos;
}

int Entity::get_x_pos()
{
	return x_pos;
}

char Entity::get_display()
{
	return display;
}

void Entity::set_ypos(int _y_pos)
{
	y_pos = _y_pos;
}

void Entity::set_xpos(int _x_pos)
{
	x_pos = _x_pos;
}

void Entity::move_up(int distance)
{
	y_pos -= distance;
}

void Entity::move_down(int distance)
{
	y_pos += distance;
}

void Entity::move_left(int distance)
{
	x_pos -= distance;
}

void Entity::move_right(int distance)
{
	x_pos += distance;
}
