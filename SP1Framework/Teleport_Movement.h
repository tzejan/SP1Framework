#include <iostream>
#include "game.h"
#include "LoadMap.h"

using namespace std;

extern struct SGameChar g_sChar;
extern enum EKEYS;
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern unsigned int mapSizeWidth;
extern unsigned int mapSizeHeight;

extern struct teleporter portalPos[26];
extern bool newMap;


void teleport_player();
void returnNextPosition(int currentPositionY, int currentPositionX);