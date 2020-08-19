#pragma once
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
	void Draw(string filepath);


};

