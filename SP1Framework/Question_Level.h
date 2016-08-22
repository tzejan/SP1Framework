#include <iostream>
#include "game.h"

using namespace std;

extern Console g_Console;
extern struct SGameChar g_sChar;
extern char map[50][150];
extern enum EKEYS;

extern char currentMap[50][150];
extern short charLoX;
extern short charLoY;

void saveMap();
void loadQ(int qNum);
void Question_Asn(bool isTrue);
void Question_resolved();
void reprint_map(int width, int height);