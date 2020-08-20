#pragma once
#include "Framework/console.h"
#include "game.h"
#include "MapMaker.h"
#include <windows.h>


class Entity
{
protected:
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
	
	//Set COORD or X and Y pos separately
	void set_pos(COORD _c);
	void set_ypos(int _y_pos);
	void set_xpos(int _x_pos);

	//Get/Set Entity's symbol
	char get_display();
	void set_display(char _display);

	//check if collision with COORD.
	//does collision code.
	virtual bool collide(COORD entity_pos) = 0;
	virtual bool collide(int entity_xpos, int entity_ypos) = 0;

	//Move based on enum EKEYS button pressed
	virtual void move(int button_pressed) = 0;

};
