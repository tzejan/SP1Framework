#include <iostream>
#include <fstream> //Test for file opening
#include <string>
#include "game.h"

using namespace std;

extern char map[50][150];

extern struct teleporter portalPos[26];

void loadMap(int level);