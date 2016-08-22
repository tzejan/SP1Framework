#include <iostream>
#include "game.h"
#include "LoadMap.h"
#include "Question_Level.h"

using namespace std;

extern struct SGameChar g_sChar;
extern enum EKEYS;
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern unsigned int mapSizeWidth;
extern unsigned int mapSizeHeight;

extern struct teleporter portalPos[26];

void Movement_Tut();
void returnPosition(int currentPositionY, int currentPositionX);