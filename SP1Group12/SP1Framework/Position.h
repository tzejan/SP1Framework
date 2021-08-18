#pragma once
class Position {
public:
	Position::Position();
	Position::~Position();
	Position::Position(int a, int b);

	int Position::get_x(void);
	void Position::set_x(int a);

	int Position::get_y(void);
	void Position::set_y(int a);

private:
	int x, y;

};

