#pragma once
#include <string>
class LevelMap
{
private:
	char MapArray[80][25]{};
public:
	 LevelMap();
	 void Load(void);
	 char Get2DArray(int i , int j);
	 
};

