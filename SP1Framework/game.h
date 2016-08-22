#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

//For other cpp
#include "LoadMap.h"
#include "PrintMap.h"
#include "PushBox_Level.h"
#include "PushBox_Movement.h"
#include "Levers_Level.h"
#include "Levers_Movement.h"
#include "Teleport_Movement.h"
#include "Question_Level.h"
#include "Question_Movement.h"
#include "Tutorial_Movement.h"
//#include "CollisionDetection.h"
#include <fstream> //File opening
#include <string>
using namespace std;


extern CStopWatch g_swTimer;
extern bool g_bQuitGame;

// Enumeration to store the control keys that your game will have
enum EKEYS
{
	K_CTRL,
	K_ALT,
	K_UP,		//Character Move up
	K_DOWN,		//Character Move down
	K_LEFT,		//Character Move left
	K_RIGHT,	//Character Move right
	K_ESCAPE,	//Quit game
	K_SPACE,	//Character interaction key
	K_ENTER,
	K_D1,
	K_D2,
	K_D3,
	K_D4,
	K_LSHIFT,
	K_COUNT //Put this last thx
};

// Enumeration for the different screen states
enum EGAMESTATES
{
    S_SPLASHSCREEN,
	S_MAIN_MENU,
    S_GAME_TUT,			//Level tutorial 
	S_GAME_1,		//Level 1
	S_GAME_2,		//Level 2
	S_GAME_3,		//Level 3
	S_GAME_4,		//Level 4
    S_COUNT
};

// struct for the game character
struct SGameChar
{
    COORD m_cLocation;
    bool  m_bActive;
};

struct teleporter
{
	char character;
	int Portal_1_X;
	int Portal_1_Y;
	int Portal_2_X;
	int Portal_2_Y;
};

void init        ( void );      // initialize your variables, allocate memory, etc
void getInput    ( void );      // get input from player
void update      ( double dt ); // update the game and the state of the game
void render      ( void );      // renders the current state of the game to the console
void shutdown    ( void );      // do clean up, free memory

void splashScreenWait();    // waits for time to pass in splash screen
void gameplay();            // gameplay logic
void moveCharacter();       // moves the character, collision detection, physics, etc
void processUserInput();    // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();         // clears the current screen and draw from scratch 
void renderSplashScreen();  // renders the splash screen
void renderGame();          // renders the game stuff
void renderMap();           // renders the map to the buffer first
void renderCharacter();     // renders the character into the buffer
void renderFramerate();     // renders debug information, frame rate, elapsed time, etc
void renderToScreen();      // dump the contents of the buffer to the screen, one frame worth of game

void renderMainMenu();      // renders the main menu

void resetLevel();			// Reset the game level

#endif // _GAME_H
