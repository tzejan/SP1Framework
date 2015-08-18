#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_COUNT
};

void init		( void );       // initialize your variables, allocate memory, etc
void getInput	( void );		// get input from player
void update		( double dt );	// update the game and the state of the game
void render		( void );       // renders the current state of the game to the console
void shutdown	( void );       // do clean up, free memory

#endif // _GAME_H