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
	char score;
	std::ifstream tr, rh, lh;
	std::string trs, rhs, lhs;

public:
	gamestate update(Graphics&);
	void play();
	void read();
	void draw(Graphics&);
	toiletroll();
};


#endif