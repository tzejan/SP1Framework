#pragma once
class Entity
{
public:
	int getposX();
	int getposY();
	void setposX(int X);
	void setposY(int X);
	Entity();
	~Entity();
	virtual char getIcon() = 0;
	virtual void move(Map&);
	virtual void move(char);
	void setDaPos(Map&, int, int, int, int);
};



