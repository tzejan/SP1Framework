#pragma once

//Position class is meant to store the entity / tile position.
//Has an x and y axis following the coordinate system.

class Position
{
private:
	int x_axis;
	int y_axis;
public:
	//constructors and destructors
	Position();
	Position(int x, int y);
	~Position();

	//getters
	int get_x_axis();
	int get_y_axis();
	bool get_out_of_bounds();

	//setters
	void set_x_axis(int x);
	void set_y_axis(int y);
	void set_coordinates(int x, int y);
	
	//others
	bool is_equal_position(Position& another_pos);
};

