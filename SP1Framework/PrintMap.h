#include <iostream>
#include "Framework\console.h"
#include <time.h>

using namespace std;

extern Console g_Console;
extern char map[50][150];
extern int timeRemaining;


void printMap(int width, int height, bool *timer, bool isMainMenu);
void deleteMap(int width, int height);