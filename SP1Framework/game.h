#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
    K_COUNT
};

void gameplay();
void printMap();
void options();

int play();
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

void scoreboard();
void startscreen();
void endscreen();
void gameover();

void difficulty();
void modes();

void effects();

void getcolumn();
void checkcollision();

void PatternAlgorithm1();
void PatternAlgorithm2();
void PatternAlgorithm3();


struct map
{
	bool fruitcheck[9];				//Rows inside one column
	unsigned char character[10];
	int color[9];
};

struct basket
{
	COORD location;
};

enum diff
{
	EASY = 1,
	NORMAL,
	HARD,
};

enum state 
{ 
	GAME = 1,
	OPTIONS,
	SCOREBOARD,
	HOME, 
	MAINMENU,
	ONE = 1,
	TWO,
	THREE,
	END
};


#endif // _GAME_H