#pragma once

class Entity
{
private:
	int x_pos;
	int y_pos;
	char display;
public:
	Entity(int y_pos, int x_pos, char display);
	int get_x_pos();
	int get_y_pos();
	char get_display();
	void set_ypos(int _y_pos);
	void set_xpos(int _x_pos);
	void move_up(int distance);
	void move_down(int distance);
	void move_left(int distance);
	void move_right(int distance);


};