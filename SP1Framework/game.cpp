// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include "Graphics.h"
#include "TableFlip.h"

double elapsedTime;
double deltaTime;
Graphics console;

gamestate state = TABLE_FLIP;
void init()
{
    elapsedTime = 0.0;
}

void shutdown()
{
}

void update(double dt)
{

    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	switch(state)
	{
	case MAIN_MENU:
		//run main menu();
		g_quitGame = true;
		break;
	case TABLE_FLIP:
		state = updateTableFlip(dt);
		break;
	case TOILET_ROLL:
		//run toiletroll minigame();
		break;
	case QUIT_GAME:
		g_quitGame = true;
		break;
	}
}

void render()
{
	switch(state)
	{
	case MAIN_MENU:
		//draw main menu();
		break;
	case TABLE_FLIP:
		drawTableFlip(&console);
		break;
	case TOILET_ROLL:
		//draw toiletroll minigame();
		break;
	}


	//Updates console to current screen
	console.updateconsole();    
}
