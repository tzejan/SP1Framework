#include "Map.h"
#include "Framework\console.h"
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

void Map::chooseMap(int lvl, Console& console)
{
	switch (lvl)
	{
	case 1:
		std::fstream tutorialLevel("Tutorial level.txt");
		printMap(tutorialLevel, rowBig, columnBig, console);
		break;
	}		
}

void Map::printMap(std::fstream& level, int row, int column, Console& console)
{
	COORD c = console.getConsoleSize();
	std::string output;
	int** mapArray = new int* [row];

	for (int y = 0; y < row; y++)
	{
		*(mapArray + y) = new int[column];
		getline(level, output);
		c.Y++;
		for (int x = 0; x < column; x++)
		{
			int value;
			value = output[x] - 48;
			*(*(mapArray + y) + x) = value;
			switch (*(*(mapArray + y) + x))
			{
			case 0:
				console.writeToBuffer(c, ' ', 0xFF);
			case 1:
				console.writeToBuffer(c, ' ', 0x88);
			case 2:
				console.writeToBuffer(c, ' ', 0x66);
			case 3:
				console.writeToBuffer(c, ' ', 0x100);
			case 4:
				console.writeToBuffer(c, ' ', 0x100);
			}
			c.X++;
		}
	}
}

/*
void Map::printMapValues(std::fstream& level, Console& console)
{
	COORD c;
	std::string output;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	const int row = 50, column = 160;
	COORD mapArray[row][column];

	for (int r = 0; r < row; r++)
	{
		c.Y++;
		getline(level, output);
		for (int c = 0; c < column; c++)
		{
			int value;
			value = output[c] - 48;
			mapArray[c.Y][c.X] = value;
			switch (mapArray[r][c])
			{
			case 0:
				console.writeToBuffer(c, ' ', 0xFF);
			case 1:
				console.writeToBuffer(c, ' ', 0x88);
			case 2:
				console.writeToBuffer(c, ' ', 0x66);
			case 3:
				console.writeToBuffer(c, ' ', 0x100);
			case 4:
				console.writeToBuffer(c, ' ', 0x100);
			}
		}
	}
}
*/
