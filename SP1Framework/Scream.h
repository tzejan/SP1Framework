#ifndef _SCREAM_H
#define _SCREAM_H

#include "game.h"
#include "Framework\console.h"

class Scream
{
private:
	bool gameends;
	bool gamestarts;
public:
	Scream();
	~Scream();
	gamestate updateScream();
	void drawScream();
};

#endif