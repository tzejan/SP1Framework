#pragma once
class Camera
{
private:
	int camx, camy;

public:
	Camera();
	~Camera();

	void setCamX(int x);
	void setCamY(int y);

	int getCamX();
	int getCamY();

};

