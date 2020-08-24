#pragma once
#include "Framework/console.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Entity.h"


/*hi*/

using namespace std;

class MapMaker
{
private:	
	
public:
	MapMaker();
	~MapMaker();
	char MapArray[20][100];
	//Takes the Txt file and puts it into the array
	void Load(string filepath);

	//Renders the Contents of the text file from origin point coord
	void Render(COORD origin, COORD end, Console& g_Console);
	void Render(SHORT origin_x, SHORT origin_y, SHORT end_x, SHORT end_y, Console& g_Console);

	//Gets character from Coordinate
	char getFromCoord(COORD c);
	char getFromCoord(SHORT x, SHORT y);
	
};

