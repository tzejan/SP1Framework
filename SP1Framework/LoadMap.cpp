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
			mapname = "Maps_Levels/Tutorial.txt"; 
			break;
		case 3: 
			mapname = "Maps_Levels/Levers.txt"; //Level 1
			break;
		case 4: 
			mapname = "Maps_Levels/Questions.txt"; //Level 2
			break;
		case 5:
			mapname = "Maps_Levels/Boxes.txt"; //Level 3
			break;
		case 6:
			mapname = "Maps_Levels/Teleportal.txt"; //Level 4
			break;
	}
	
	
	//Function use to store data from text file to 2d array
	string line = " ";
	//clear 2d array / portal locations
	memset(map, '\0', sizeof(map[0][0]) * 50 * 150);
	memset(portalPos, '\0', sizeof(portalPos[0]) * 26);

	//store to array
	ifstream myfile(mapname);
	int row = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			if (level == 6)
			{
				//Write code to start storing coordinates here
				//Store all teleport location here
				//Store location in array or struct
				//Run a double for loop if possible _Assignemt 2 common letter 
			}
			

			for (int i = 0; i <= line.length(); i++)
			{
				if (line[i] == '#')
					map[row][i] = (char)219;
				else if (line[i] == 'D' && level == 5) //Level control printing if u want this on ur level change to (level == 5 || level == 6)
					map[row][i] = (char)186;
				else if (line[i] == 'B' && level == 5) //Level control printing
					map[row][i] = (char)254;
				else if ((line[i] >= 65 && line[i] <= 90) && (line[i] != 'E') && level == 6) //Level control printing
				{
					map[row][i] = (char)233; //Place holder currently
				}
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
