// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
<<<<<<< HEAD
#include "Graphics.h"
#include "TableFlip.h"
<<<<<<< HEAD
=======
>>>>>>> parent of fffa12d... Stuff

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
<<<<<<< HEAD
Graphics TableFlip;

=======
#include "Scream.h"
=======
>>>>>>> parent of fffa12d... Stuff

double elapsedTime;
double deltaTime;
Graphics console;
>>>>>>> origin/master

//Create a pointer to store the location of the scream object
Scream* scream;

gamestate state = TABLE_FLIP;
void init()
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	scream = NULL;
>>>>>>> origin/master
=======
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y / 2;

>>>>>>> parent of fffa12d... Stuff
    elapsedTime = 0.0;
}

void shutdown()
{
<<<<<<< HEAD
<<<<<<< HEAD

=======
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
>>>>>>> parent of fffa12d... Stuff
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
<<<<<<< HEAD
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
=======
>>>>>>> origin/master
=======
>>>>>>> parent of fffa12d... Stuff
}

void update(double dt)
{
<<<<<<< HEAD
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        Beep(1440, 30);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        Beep(1440, 30);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        Beep(1440, 30);
        charLocation.X++; 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
=======
	switch(state)
	{
	case MAIN_MENU:
		//run main menu();
		g_quitGame = true;
		break;
	case TABLE_FLIP:
		state = updateTableFlip(&console);
		break;
	case TOILET_ROLL:
		//run toiletroll minigame();
		break;
	case SCREAM:
		//create the scream object if it doesn't exist
		if(scream == NULL)
		{
			scream = new Scream(console);
		}
		state = scream->update();
		//deletes the scream once the game changes state and makes the scream pointer NULL again
		if(state != SCREAM)
		{
			delete scream;
			scream = NULL;
		}
		break;
	case QUIT_GAME:
		g_quitGame = true;
		break;
	}
>>>>>>> origin/master
}

void render()
{
<<<<<<< HEAD
<<<<<<< HEAD
	drawTableFlip(&TableFlip);
	TableFlip.updateconsole();
=======
	//Updates console to current screen
	console.updateconsole();    
>>>>>>> origin/master
=======
    // clear previous screen
    colour(0x0F);
    cls();

    //render the game

    //render test screen code (not efficient at all)
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
	for (int i = 0; i < 12; ++i)
	{
		gotoXY(3*i,i+1);
		colour(colors[i]);
		std::cout << "WOW";
	}

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

    
>>>>>>> parent of fffa12d... Stuff
}
