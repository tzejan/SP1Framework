#include <iostream>
#include <fstream> //Test for file opening
#include <string>

using namespace std;

extern char map[50][150];
extern int portalPos[26];
extern struct teleporter;

void loadMap(int level);