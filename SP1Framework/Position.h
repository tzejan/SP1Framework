#pragma once
class position
{
private:
	int x;
	int y;
public:
	position();
	position(int x, int y);
	~position();

	//gettters
	int GetXY(char xy);

	//setters
	void SetXY(char xy, int value);

};

