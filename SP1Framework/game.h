#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch timer;
extern bool g_continueGame;


void init();
void shutdown();
void getInput();
void render();
bool update();

#endif // _GAME_H