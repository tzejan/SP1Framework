#pragma once
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class MapMaker
{
private:
	char MapArray[20][100];
public:
	MapMaker();
	~MapMaker();

	void Draw(string filepath);

	

};

