#include <iostream>
#include "Framework\console.h"
#include <time.h>
#include "game.h"

using namespace std;

extern Console g_Console;
extern char map[50][150];
extern int timeRemaining;
extern int *changeHealth;
extern struct SGameChar  g_sChar;
extern bool deleteChar;

void printMap(int width, int height, bool *timer, bool isMainMenu, bool *health);
void deleteMap(int width, int height);