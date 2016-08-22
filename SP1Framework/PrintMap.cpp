#include "PrintMap.h"

void printMap(int width, int height, bool *timer, bool isMainMenu, bool instructions, bool *health)
{
	double timeToWait = 1.0;

	//Prints the map info
	COORD c = g_Console.getConsoleSize();
	c.X = c.X / 2 - width;
	c.Y = c.Y / 2 - height;
	string line = " ";
	for (int row = 0; row <= (height*2); row++)
	{
		line = map[row];
		g_Console.writeToBuffer(c, line);
		c.Y++;
	}
	if (isMainMenu)
	{
		c.X += 44 - 10;
		c.Y++;
		if (menuPointer == 0)
		{
			g_Console.writeToBuffer(c, "-> Start Game!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "Instructions!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "Quit Game!", 0x0C);
		}
		else if (menuPointer == 1)
		{
			g_Console.writeToBuffer(c, "Start Game!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "-> Instructions!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "Quit Game!", 0x0C);
		}
		else if (menuPointer == 2)
		{
			g_Console.writeToBuffer(c, "Start Game!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "Instructions!", 0x0A);
			c.Y++;
			g_Console.writeToBuffer(c, "-> Quit Game!", 0x0C);
		}
		
	}
	if (instructions)
	{
		c.X += width - 9;
		c.Y++;
		g_Console.writeToBuffer(c, "Escape to go back!", 0x0A);
	}
	if (*timer == true)
	{
		if (timeRemaining > 0)
		{
			c.X += width - 17;
			c.Y++;
			g_Console.writeToBuffer(c, "You only have " + to_string(timeRemaining) + " seconds remaining");
		}
		else
		{
			c.X += width - 4;
			c.Y++;
			g_Console.writeToBuffer(c, "OVERTIME", 0x0C);
		}
		
	}
	if (*health == true)
	{
		if (*timer == true)
		{
			if (timeRemaining > 0)
			{
				c.X += width + 5;
				c.Y -= 37;
			}
			else
			{
				c.X += width - 8;
				c.Y -= 37;
			}
		}
		else
		{
			c.X += width + 50;
			c.Y -= 38;
		}
		if (*changeHealth != 0)
		{
			for (int i = *changeHealth; i > 0; i--)
			{
				g_Console.writeToBuffer(c, (char)3, 0x0C);
				c.X += 2;
			}
		}

	}
}

void deleteMap(int width, int height) //Activates at level Teleporter only
{
	for (int row = (height * 2)-1; row >= 0; row--)
	{
		for (int col = (width * 2)-1; col >= 0; col--)
		{
			if (map[row][col] != (char)255)
			{
				map[row][col] = (char)255;
				break;
			}
		}
	}
}