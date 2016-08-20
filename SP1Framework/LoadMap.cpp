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

	//store to array
	ifstream myfile(mapname);
	int row = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{	
			for (unsigned int i = 0; i <= line.length(); i++)
			{
				if (line[i] == '#')
					map[row][i] = (char)219;
				else if (line[i] == 'D' && (level == 5 || level == 3 || level == 4)) //Level control printing if u want this on ur level change to (level == 5 || level == 6)
					map[row][i] = (char)186;
				else if (line[i] == 'B' && level == 5) //Level control printing
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

	
	//Store to struct (Test)
	if (level == 6)
	{
		int portals = 0;
		memset(portalPos, 0, sizeof(portalPos));
		//Write code to start storing coordinates here
		//Store all teleport location here
		//Store location in array or struct
		//Run a double for loop if possible _Assignemt 2 common letter 
		for (int row = 0; row < 50; row++)//Finds the first row for first letter
		{
			if (map[row] == '\0')
			{
				continue;
			}
			else
			{
				for (int col = 0; col < 150; col++) //Finds the colums for first letter
				{
					if (map[row][col] == '\0')
					{
						continue; //Dont find any thing
					}
					else if ((map[row][col] >= 65 && map[row][col] <= 90) && (map[row][col] != 'E')) //Check if its the letter i want
					{
						portalPos[portals].character = map[row][col]; //Store the letter in the array / struct given in global variable
						for (int row2 = row+1; row2 < 50; row2++)
						{
							for (int col2 = 0; col2 < 150; col2++) //Runs another for loop to find the second letter
							{
								if (map[row2][col2] == '\0')
								{
									continue;//Dont find any thing
								}
								else if ((portalPos[portals].character == map[row2][col2]) && map[row2][col2]!=(char)233) //Found second letter
								{
									//Store both positions here (MAX. 26)
									map[row2][col2] = (char)233;
									map[row][col] = (char)233;
									portalPos[portals].Portal_1_X = row;
									portalPos[portals].Portal_1_Y = col;
									portalPos[portals].Portal_2_X = row2;
									portalPos[portals].Portal_2_Y = col2;
									portals+=1;
								}
							}
						}
					}
				}
			}
		}
	}

}
