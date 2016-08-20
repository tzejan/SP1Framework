#include <iostream>
#include "game.h"

using namespace std;

extern struct SGameChar g_sChar;
extern enum EKEYS;
extern double  g_dElapsedTime;
extern double  g_dBounceTime;
extern unsigned int mapSizeWidth;
extern unsigned int mapSizeHeight;

void qMovement();