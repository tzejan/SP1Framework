#include "Map.h"
#include <iostream>
#include <string>

Map::Map()
{
	for (int i = 0; i < 20; i++) // x
	{
		for (int i2 = 0; i2 < 20; i2++) // y
		{
			GameMap[i][i2] = ' ';
		}
	}
}

Map::~Map()
{
}

void Map::PrintGameMap(void) const
{
	std::string Output = "";
	//std::cout << " 12345678901234567890";  //UI
	for (int i = 1; i < 21; ++i) // x
	{
		//if (i >= 10)
		//{
		//	std::cout << std::endl << i % 10; //UI
		//}
		//else
		//{
		//	std::cout << std::endl << i;  //UI
		//}
		for (int i2 = 1; i2 < 21; i2++) // y
		{
			Output += GameMap[i-1][i2-1];
		}
		Output+= "\n";
	}
	std::cout << Output;
}

void Map::SetGameMap(int x, int y, char symbol)
{
	this->GameMap[x-1][y-1] = symbol;
}

std::string Map::GetMapChosen(int MapLevel)
{
	if (MapLevel == 1)
	{
		return "WWWWWWW,WW   WW,WW P WW,WW   WW,WWW WWW,WWW WWW,WWW WWW,WWW WWW,WWW  WW,WW R WW,WWW WWW,WW  WWW,WW R WW,WWW WWW,WWW WWW,WWW WWW,WW   WW,WW T WW,WW   WW,WWWWWWW";
	}
	else if (MapLevel == 2)
	{
		return "WWWWWWWWWWW,WWWWWWWWWWW,WWW  P  WWW,WWW     WWW,WWW     WWW,WWWWWSWWWWW,WWWWW   WWW,WWWWWWW WWW,WWWW S  WWW,WWWW SRWWWW,WWWW  R WWW,WWWWWW WWWW,WWWWW   WWW,WWWWW T WWW,WWWWW   WWW,WWWWWWWWWWW";

	}
	else if (MapLevel == 3)
	{
		return "WWWWWWWWW,WWWWW P W,WWWWW   W,W  W    W,WK  S   W,W W S   W,WWWWWiIiW,WWWWWIiIW,WWWWWiIiW,WWWWWIiIW,WWWWWiIiW,WWWWWWLWW,WWWWW   W,WWWWW R W,WWWWW   W,WWWWWWWWW";
	}
	else if (MapLevel == 4)
	{
		return "WWWWWWWWWWW,WWWPL   WWW,WWW W T WWW,W   W   WWW,W W WWWWWWW,W I S     W,WIW WWW W W,WIWWWWW W W,WI  S   W W,WIWWIWWWW W,WIWWIWWWW W,W    K    W,WWWWWWWWWWW,WWWWWWWWWWW,WWWWWWWWWWW,WWWWWWWWWWW";
	}
	else if (MapLevel == 5)
	{
	}
	else if (MapLevel == 6)
	{
	}
	else if (MapLevel == 7)
	{
	}
	else if (MapLevel == 8)
	{
	}
	else if (MapLevel == 9)
	{
	}
	else if (MapLevel == 10)
	{
	}
	else
	{
		return "";
	}
}

int Map::GetMapMoves(int MapLevel)
{
	if (MapLevel == 1)
	{
		return 21;
	}
	else if (MapLevel == 2)
	{
		return 22;
	}
	else if (MapLevel == 3)
	{
		return 26;
	}
	else if (MapLevel == 4)
	{
		return 44;
	}
	else if (MapLevel == 5)
	{

	}
	else if (MapLevel == 6)
	{
	}
	else if (MapLevel == 7)
	{
	}
	else if (MapLevel == 8)
	{
	}
	else if (MapLevel == 9)
	{
	}
	else if (MapLevel == 10)
	{
	}
	else
	{
		return 0;
	}
}


