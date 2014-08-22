// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include "Graphics.h"
#include "TableFlip.h"
#include "Scream.h"

double elapsedTime;
double deltaTime;
Graphics console;

//Create a pointer to store the location of the scream object
Scream* scream;

gamestate state = TABLE_FLIP;
void init()
{
	scream = NULL;
    elapsedTime = 0.0;
}

void shutdown()
{
}

void update(double dt)
{
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
}

void render()
{
	//Updates console to current screen
	console.updateconsole();    
}
