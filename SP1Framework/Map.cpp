#include "Map.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>

Map::Map(): rowSmall{ 25 }, columnSmall{ 80 }, rowBig{ 50 }, columnBig{ 160 }
{
}

Map::~Map()
{
}

int Map::getRowSmall()
{
	return rowSmall;
}

int Map::getColumnSmall()
{
	return columnSmall;
}

int Map::getRowBig()
{
	return rowBig;
}

int Map::getColumnBig()
{
	return columnBig;
}

void Map::chooseMap(int lvl)
{
	switch (lvl)
	{
	case 1:
		std::fstream tutorialLevel("Tutorial level.txt");
		printMap(tutorialLevel, rowBig, columnBig);
		break;
	}		
}

void Map::printMap(std::fstream& level, int row, int column)
{
	std::string output;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int** mapArray = new int* [row];

	for (int r = 0; r < row; r++)
	{
		*(mapArray + r) = new int[column];
		getline(level, output);

		for (int c = 0; c < column; c++)
		{
			int value;
			value = output[c] - 48;
			*(*(mapArray + r) + c) = value;
			if (*(*(mapArray + r) + c) == 0) { SetConsoleTextAttribute(hConsole, 255 | 255); std::cout << *(*(mapArray + r) + c); } //255 = white, 256 = black
			if (*(*(mapArray + r) + c) == 1) { SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | FOREGROUND_BLUE); std::cout << *(*(mapArray + r) + c); }
			if (*(*(mapArray + r) + c) == 2) { SetConsoleTextAttribute(hConsole, BACKGROUND_RED | FOREGROUND_RED); std::cout << *(*(mapArray + r) + c); }
			if (*(*(mapArray + r) + c) == 3) { SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_GREEN); std::cout << *(*(mapArray + r) + c); }
			if (*(*(mapArray + r) + c) == 4) { SetConsoleTextAttribute(hConsole, 256 | 256); std::cout << *(*(mapArray + r) + c); }
		}
	}


}
