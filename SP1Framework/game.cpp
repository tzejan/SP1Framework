// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include "MainMenu.h"
#include"ToiletRoll.h"
#include "Graphics.h"
#include "TableFlip.h"
#include "Scream.h"
#include "subgame.h"


Graphics console;

//Create a pointer to store the location of the scream object
Scream* scream;
toiletroll* toilet;

gamestate state = SUBMARINE;
void init()
{
	updateinput();
	ini();
	initialisesubdrawings();
	scream = NULL;
	toilet = NULL;
}

void shutdown()
{
}

void update(double dt)
{
	updateinput();
	switch(state)
	{
	case INTRO:
		Intro(console);
		break;
	case MAIN_MENU:
		MainMenu(console);
		break;
	case TABLE_FLIP:
		state = updateTableFlip(&console);
		break;
	case SUBMARINE:
		state = playsubgamemain(&console);
		break;
	case TOILET_ROLL:
		//create the toiletroll object if it doesn't exist
		if(toilet == NULL)
		{
			toilet = new toiletroll(console);
		}
		state = toilet->update();
		//deletes the toiletroll once the game changes state and makes the scream pointer NULL again
		if(state != TOILET_ROLL)
		{
			delete toilet;
			toilet = NULL;
		}
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
	console.updateconsole();
}
