#include "LevelMap.h"
#include <fstream>
#include <iostream>
#include "Framework\console.h"
#include "game.h"
using namespace std;
LevelMap::LevelMap()
{
}

void LevelMap::Load(void)
{
	char character;
	string Length;
	int x = 0;
	int row = 0;
	int col = 0;
	std::string str = " ";
	ifstream Level1;
	Level1.open("Level1.txt");
	if (!Level1)
	{
		cerr << "Unable to open file";
		exit(1); // terminate with error
	}
	for (int i = 0; i < 80; ++i)
	{
		for (int j = 0; j < 25; ++j)
		{
			Level1 >> MapArray[i][j];
		}
	}
}

char LevelMap::Get2DArray(int i , int j)
{
	return MapArray[i][j];
	i += 1;
	j += 1;
}





