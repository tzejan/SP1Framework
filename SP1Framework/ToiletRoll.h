#ifndef _TOILETROLL_H
#define _TOILETROLL_H

#include "game.h"
#include "Framework\console.h"
#include "Graphics.h"
#include <fstream>
#include <string>

class toiletroll
{
private:
	int CurrentFrame;
	bool GameStarts;
	bool gameends;
	int y;
	int rx;
	int lx;
	int score;
	std::ifstream tr, rh, lh;
	std::string trs, rhs, lhs;
	Graphics& console;

public:
	gamestate update();
	void play();
	void read();
	void draw();
	toiletroll(Graphics&);
};


#endif