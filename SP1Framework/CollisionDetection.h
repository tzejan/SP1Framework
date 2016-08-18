#include <iostream>
#include <string>
#include "Framework\console.h"
#include "game.h"

using namespace std;

//Global variable put here
extern char map[50][150]; //Map
extern Console g_Console; //Player position

bool collisionDetect(EKEYS direction);