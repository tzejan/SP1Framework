// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include "Graphics.h"
#include "TableFlip.h"
<<<<<<< HEAD

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
Graphics TableFlip;

=======
#include "Scream.h"

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
=======
	scream = NULL;
>>>>>>> origin/master
    elapsedTime = 0.0;
}

void shutdown()
{
<<<<<<< HEAD

}

void getInput()
{    
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
=======
>>>>>>> origin/master
}

void update(double dt)
{
<<<<<<< HEAD
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	updateTableFlip();

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
	drawTableFlip(&TableFlip);
	TableFlip.updateconsole();
=======
	//Updates console to current screen
	console.updateconsole();    
>>>>>>> origin/master
}
