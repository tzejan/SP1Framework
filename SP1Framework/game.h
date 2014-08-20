#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Directory.h"

extern StopWatch g_timer;
extern bool g_quitGame;
extern bool PlayGame;

enum Sequence
{
	TITLE,
	GAME,
	RESULTS,
	WIN,
	LOSE,
	END_GAME,
	MAX_SEQUENCE
};

enum KeysGame
{
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_ENTER,
    K_COUNT
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory
void tableflip();

#endif // _GAME_H