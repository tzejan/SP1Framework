#include "Map.h"
#include "Framework\console.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <iostream>

Map::Map(): row{ 25 }, column{ 80 }
{
	//small is the normal console size, big is the map size.
}

Map::~Map()
{
}

int Map::getRow()
{
	return row;
}

int Map::getColumn()
{
	return column;
}

void Map::chooseMap(int lvl, Console& console) //this is to choose the map to print out
{
	switch (lvl)
	{
	case 0:
	{
		std::fstream menu("MainMenu.txt");
		printMap(menu, row, column, console);
		break;
	}
	case 1:
	{
		std::fstream tutorialLevel("Tutorial level.txt");
		printMap(tutorialLevel, row, column, console);
		break;
	}
	}
}

//put in the level you want to print out, the size of how big it will be and the console obj
//if unsure follow case 1 example.
void Map::printMap(std::fstream& level, int row, int column, Console& console)
{
	COORD c = console.getConsoleSize();
	std::string output;
	int** mapArray = new int* [row];

	for (int y = 0; y < row; y++)
	{
		c.Y = y;
		*(mapArray + y) = new int[column];
		getline(level, output);
		
		for (int x = 0; x < column; x++)
		{
			c.X = x;
			int value;
			value = output[x] - 48;
			*(*(mapArray + y) + x) = value;
			switch (*(*(mapArray + y) + x))
			{
			case 0:
				console.writeToBuffer(c, ' ', 0xF0); //white
				break;
			case 1:
				console.writeToBuffer(c, ' ', 0x88); //gold
				break;
			case 2:
				console.writeToBuffer(c, ' ', 0x66); //dark gray
				break;
			case 3:
				console.writeToBuffer(c, ' ', 0x77); //light gray
				break;
			case 4:
				console.writeToBuffer(c, ' ', 0x00); //black
				break;
			}
		}

		//for (int y = 0; y < row; y++)
		//{
		//	delete[] (mapArray + y);
		//}

		//delete[] mapArray;
	}

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//figure out how to delete map ltr
}
