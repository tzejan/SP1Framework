#include "Question_Level.h"

// temporarily store map
char currentMap[50][150];
// temporarily store character location
short charLoX;
short charLoY;
//map size
unsigned int mwidth = 126 / 2;
unsigned int mheight = 36 / 2;
// usage of keys
extern bool g_abKeyPressed[K_COUNT];

void saveMap() // save the current state of the map
{
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 150; j++)
		{
			currentMap[i][j] = map[i][j];//find and save current map to array
		}
	}

	charLoX = g_sChar.m_cLocation.X;// saves the character's location
	charLoY = g_sChar.m_cLocation.Y;
}

void loadQ(int qNum)
{
	string mapname = " ";
	switch (qNum)
	{
	case 0:
		mapname = "Maps_Text/Q0.txt";
		break;
	case 1:
		mapname = "Maps_Text/Q1.txt";
		break;
	case 2:
		mapname = "Maps_Text/Q2.txt";
		break;
	case 3:
		mapname = "Maps_Text/Q3.txt";
		break;
	case 4:
		mapname = "Maps_Text/Q4.txt";
		break;
	case 5:
		mapname = "Maps_Text/Q5.txt";
		break;
	case 6:
		mapname = "Maps_Text/Q6.txt";
		break;
	case 7:
		mapname = "Maps_Text/Q7.txt";
		break;
	case 8:
		mapname = "Maps_Text/Q8.txt";
		break;
	case 9:
		mapname = "Maps_Text/Q9.txt";
		break;
	case 10:
		mapname = "Maps_Text/Q10.txt";
		break;
	case 11:
		mapname = "Maps_Text/Q11.txt";
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

void Question_Asn(bool isTrue) //what happens if a question is answered correctly
{
	if (isTrue)
	{
		clearScreen();
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 150; j++)
			{
				map[i][j] = currentMap[i][j];
			}
		}

		reprint_map(mwidth, mheight);

		g_sChar.m_cLocation.X = charLoX;
		g_sChar.m_cLocation.Y = charLoY;
		renderCharacter();
		Question_resolved();
	}
}

void Question_resolved() //deleting doors, ? marks, and resetting the temporary fields
{
	if (map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X + 1) - (90 - mwidth)] == (char)186)
	{
		map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X + 1) - (90 - mwidth)] = (char)32;
	}
	if (map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X - 1) - (90 - mwidth)] == (char)186)
	{
		map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X - 1) - (90 - mwidth)] = (char)32;
	}
	if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] == (char)186)
	{
		map[(g_sChar.m_cLocation.Y + 1) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] = (char)32;
	}
	if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] == (char)186)
	{
		map[(g_sChar.m_cLocation.Y - 1) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] = (char)32;
	}
	if (map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] == (char)63)
	{
		map[(g_sChar.m_cLocation.Y) - (25 - mheight)][(g_sChar.m_cLocation.X) - (90 - mwidth)] = (char)32;
	}
	memset(currentMap, '\0', sizeof(currentMap[0][0]) * 50 * 150);;//clean up
	charLoX = 0;
	charLoY = 0;
}

void reprint_map(int width, int height) // reprint the map back in its original state
{
	COORD c = g_Console.getConsoleSize();
	c.X = c.X / 2 - width;
	c.Y = c.Y / 2 - height;
	string line = " ";
	for (int row = 0; row <= (height * 2); row++)
	{
		line = map[row];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
}