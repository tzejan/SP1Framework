// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using std::cout;
using std::cin;
using std::endl;

double elapsedTime;
double deltaTime;
double checkTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD charFlippingGuy;
COORD charFlippingGuy2;
COORD charFlippingGuy3;
COORD charTable;
COORD charTable2;
COORD charTableN;
COORD charTable2N;
COORD Instructions;
COORD Instructions2;
COORD consoleSize;
int LeftPower;
int RightPower;

void init()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right;
	consoleSize.Y = csbi.srWindow.Bottom;

	// set the character to be in the center of the screen.
	Instructions.X = ((consoleSize.X /2)-17);
	Instructions.Y = (consoleSize.Y/2)+9;

	Instructions2.X = ((consoleSize.X /2)-27);
	Instructions2.Y = (consoleSize.Y/2)+10;

	charLocation.X = (consoleSize.X / 2);
	charLocation.Y = (consoleSize.Y / 2);

	charTable.X = (consoleSize.X/2)-34;
	charTable.Y = (consoleSize.Y/2);

	charTable2.X = (consoleSize.X/2)-34;
	charTable2.Y = (consoleSize.Y/2)+1;

	charTableN.X = (consoleSize.X/2)+34;
	charTableN.Y = (consoleSize.Y/2);

	charTable2N.X = (consoleSize.X/2)+34;
	charTable2N.Y = (consoleSize.Y/2)+1;

	charFlippingGuy.X = (consoleSize.X/2)-38;
	charFlippingGuy.Y = (consoleSize.Y/2)-1;

	charFlippingGuy2.X = (consoleSize.X/2)-38;
	charFlippingGuy2.Y = (consoleSize.Y/2);

	charFlippingGuy3.X = (consoleSize.X/2)-38;
	charFlippingGuy3.Y = (consoleSize.Y/2)+1;

	elapsedTime = 0.0;
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
	keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;

	if(PlayGame == false)
	{
		system("pause");
		if (keyPressed[K_ENTER])
		{
			PlayGame = true;
		}
	}

	// Updating the location of the character based on the key press
	if (elapsedTime <= 7)
	{
		if (keyPressed[K_LEFT])
		{
			Beep(1440, 30);
			LeftPower = LeftPower + 1;
		}
		if (keyPressed[K_RIGHT])
		{
			Beep(1440, 30);
			RightPower = RightPower + 1;
		}
	}

	// quits the game if player hits the escape key
	if (keyPressed[K_ESCAPE])
		g_quitGame = true;  	
}

void render()
{
	// clear previous screen
	colour(0x0A);
	cls();

	// render time taken to calculate this frame
	gotoXY(72, 0);
	colour(0x1A);
	std::cout << 1.0 / deltaTime << "fps" << std::endl;

	gotoXY(0, 0);
	colour(0x1A);
	std::cout << checkTime << "secs" << std::endl;

	gotoXY(68, 1);
	colour(0x60);
	std::cout << RightPower << "RightPower" << std::endl;

	gotoXY(0, 1);
	colour(0x60);
	std::cout << LeftPower << "LeftPower" << std::endl;

	if(elapsedTime > 7)
	{
		gotoXY(23,14);
		colour(0x58);
		cout << "Your table has flipped over " << (RightPower+LeftPower)<< " tables!" << endl;
	}

	// render character
	if(elapsedTime <=7)
	{
		gotoXY(charTable);
		colour(0x58);
		cout << "-------" << endl;

		gotoXY(charTable2);
		colour(0x58);
		cout << "|     |" << endl;
	}

	gotoXY(charFlippingGuy);
	colour(0x48);
	cout << "  o" << endl;

	gotoXY(charFlippingGuy2);
	colour(0x48);
	cout << " / =" << endl;

	gotoXY(charFlippingGuy3);
	colour(0x48);
	cout << "|| " << endl;

	if(elapsedTime > 7)
	{
		gotoXY(charTableN);
		colour(0x58);
		cout << "|     |" << endl;

		gotoXY(charTable2N);
		colour(0x58);
		cout << "-------" << endl;
	}

	gotoXY(Instructions);
	colour(0x20);
	cout << "----------Instuctions----------" << endl;

	gotoXY(Instructions2);
	colour(0x20);
	cout << "Press the left and right button as much as you can!" << endl;
}

