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

	void Draw(string filepath);


};

