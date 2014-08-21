#ifndef _TOILETROLL_H
#define _TOILETROLL_H

#include "game.h"
#include "Framework\console.h"
#include "Graphics.h"

class toiletroll
{
private:
	int CurrentFramePerSec;
	bool GameStarts;
	bool gameends;

public:
	gamestate update();
	void play();
	void draw();
	toiletroll();
};

#endif