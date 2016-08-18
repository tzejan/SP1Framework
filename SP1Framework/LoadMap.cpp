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
			mapname = "Maps_Levels/Boxes.txt";
			break;
		case 3:
			mapname = "Maps_Levels/Teleportal.txt";
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
				if (line[i] == '#') //For Walls
					map[row][i] = (char)219;
				else if (line[i] == 'D' && level == 2) //For Door (Level 2 only)
					map[row][i] = (char)186;
				else if (line[i] == 'B' && level == 2) //For push blocks (Level 2 only)
					map[row][i] = (char)254;
				else
					map[row][i] = line[i]; //Print the rest as normal
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
