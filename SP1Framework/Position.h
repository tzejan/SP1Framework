#pragma once
class Position
{
private:
	int PosX;
	int PosY;
	char markLabel;

public:
	Position();
	~Position();

	void UpdatePosition(int x, int y);
	void SetMarker(char m);

	const int GetPosX();
	const int GetPosY();
	const char GetMarker();
};

