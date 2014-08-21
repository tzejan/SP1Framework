#ifndef _SCREAM_H
#define _SCREAM_H

#include "game.h"
#include "Framework\console.h"
#include "Graphics.h"

class Scream
{
private:
	//variables
	bool gameends;
	bool paused;
	int power;
	int opposingForce;
	int currFrame;
	int pauseDelay;
	Graphics& console;
	//functions
	bool play();

public:
	Scream(Graphics& console);
	~Scream();
	gamestate update();
	void draw();
};

#endif