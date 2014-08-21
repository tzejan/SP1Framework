#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"
#include "Directory.h"

extern StopWatch g_timer;
extern bool g_quitGame;

<<<<<<< HEAD

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_ENTER,
    K_COUNT
=======
enum gamestate
{
	MAIN_MENU,
	TABLE_FLIP,
	TOILET_ROLL,
	SCREAM,
	SUBMARINE,
	QUIT_GAME,
	MAXSTATES
>>>>>>> origin/master
};

const int numofminigames = MAXSTATES - 2;


void init();                // initialize your variables, allocate memory, etc
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory

#endif // _GAME_H