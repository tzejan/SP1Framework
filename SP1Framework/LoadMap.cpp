#include "LoadMap.h"

void loadMap(int level)
{
	string mapname = " ";
	switch (level)
	{
		case 0:
			mapname = "Maps_Text/Splash_Screen.txt";
			break;
		case 1:
			mapname = "Maps_Text/Main_Menu.txt";
			break;
		case 2:
			mapname = "Maps_Levels/TestMap.txt";
			break;
	}
	
	
	//Function use to store data from text file to 2d array
	string line = " ";
	//clear 2d array
	memset(map, '\0', sizeof(map[0][0]) * 50 * 150);

	//store to array
	ifstream myfile(mapname);
	int row = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			for (int i = 0; i <= line.length(); i++)
			{
				if (line[i] == '#')
					map[row][i] = (char)219;
				else
					map[row][i] = line[i];
			}
			row++;
		}
		myfile.close();
	}
	else
	{
		cout << "file cannot be opened" << endl;
	}
}