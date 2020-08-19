#pragma once
#include <windows.h>


class Entity
{
private:
	COORD c;
	char display;
public:
	Entity();
	Entity(COORD _c, char _display);
	Entity(int y_pos, int x_pos, char display);
	
	
	//Get COORD or X and Y pos separately
	COORD get_pos();
	int get_x_pos();
	int get_y_pos();
	
	//Get Entity's symbol
	char get_display();

	//Set COORD or X and Y pos separately
	void set_pos(COORD _c);
	void set_ypos(int _y_pos);
	void set_xpos(int _x_pos);
	

};
