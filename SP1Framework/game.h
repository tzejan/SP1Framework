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

int play();
void gameplay();
void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void printMap();
void options();
void scoreboard();
void startscreen();
void difficulty();
void modes();
void endscreen();
void effects();
void getcolumn();
void checkcollision();

struct map
{
	bool fruitcheck[9];			//Rows inside one column
	unsigned char character[10];
	int color[9];
};

struct basket
{
	COORD location;
};
enum diff
{
	EASY=1,
	NORMAL,
	HARD,
	GOD,
};
enum state 
{ 
	GAME = 1,
	OPTIONS,
	SCOREBOARD,
	HOME, 
	gootohell,
	ONE=1,
	TWO,
	THREE,
	END
};


#endif // _GAME_H