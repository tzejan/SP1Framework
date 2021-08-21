#pragma once
class Position
{
private:
	int x, y;
public:
	Position();
	Position(int x, int y);
	int getx() const;
	int gety() const;
	void setx(int x);
	void sety(int y);

};

