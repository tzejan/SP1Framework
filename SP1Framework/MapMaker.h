#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class MapMaker
{
private:
	
public:
	char MapArray[20][100];
	MapMaker();
	~MapMaker();

	//Takes the Txt file and puts it into the array
	void Load(string filepath);

	//Gets character from Coordinate
	char getFromCoord(COORD c);
	char getFromCoord(SHORT x, SHORT y);
	
};

