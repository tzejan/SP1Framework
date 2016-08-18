#include "PrintMap.h"

void printMap(int width, int height, bool isMainMenu)
{
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
		g_Console.writeToBuffer(c, "Press Enter To Start!", 0x0A);
		c.Y++;
		g_Console.writeToBuffer(c, "Press Escape To Exit!", 0x0C);
	}
}