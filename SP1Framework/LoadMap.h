#include <iostream>
#include <fstream> //Test for file opening
#include <string>

using namespace std;

extern char map[50][150];

struct teleporter
{
	char character;
	int Portal_1_X;
	int Portal_1_Y;
	int Portal_2_X;
	int Portal_2_Y;
};

void loadMap(int level);