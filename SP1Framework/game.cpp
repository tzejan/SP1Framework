// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

double  g_dElapsedTime;
double  g_dDeltaTime;
bool    g_abKeyPressed[K_COUNT];

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN;
double  g_dBounceTime; // this is to prevent key bouncing, so we won't trigger keypresses more than once

// Console object
Console g_Console(180, 50, "SP1 Framework");


// Bool for loading text files once
bool newMap = true;
static const int sizeWidth = 150;
static const int sizeHeight = 50;
char map[sizeHeight][sizeWidth] = {" ", };
unsigned int mapSizeWidth = 0;
unsigned int mapSizeHeight = 0;

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;
    g_dBounceTime = 0.0;

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Getting all the key press states
//            This function checks if any key had been pressed since the last time we checked
//            If a key is pressed, the value for that particular key will be true
//
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP]     = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN]   = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT]   = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT]  = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_SPACE]  = isKeyPressed(VK_SPACE);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	g_abKeyPressed[K_ENTER]  = isKeyPressed(VK_RETURN);
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : 
			splashScreenWait(); // game logic for the splash screen			 
            break;
		case S_MAIN_MENU: 
			renderMainMenu();		  
			break;
        case S_GAME: 
			gameplay(); // gameplay logic when we are in the game
            break;
    }
}
//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears thes current screen and draw from scratch (input mapping's max length and height)
    switch (g_eGameState)
    {
        case S_SPLASHSCREEN: 
			mapSizeWidth = 127/2;
			mapSizeHeight = 22/2;
			renderSplashScreen();
            break;
		case S_MAIN_MENU: 
			mapSizeWidth = 88/2;
			mapSizeHeight = 9/2;
			renderMainMenu();
			break;
        case S_GAME:
			mapSizeWidth = 124/2;
			mapSizeHeight = 36/2;
			renderGame();
            break;
    }
    renderFramerate();  // renders debug information, frame rate, elapsed time, etc
    renderToScreen();   // dump the contents of the buffer to the screen, one frame worth of game
}

void splashScreenWait()    // waits for time to pass in splash screen
{
	if (g_dElapsedTime > 5.0) // wait for 3 seconds to switch to game mode, else do nothing
	{
		newMap = true;
		g_eGameState = S_MAIN_MENU;
	}
		
}

void gameplay()            // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{
	COORD c = g_Console.getConsoleSize();
    bool bSomethingHappened = false;
    if (g_dBounceTime > g_dElapsedTime)
        return;

    // Updating the location of the character based on the key press
    // providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_sChar.m_cLocation.Y > 0)
    {
		if (map[(g_sChar.m_cLocation.Y - 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y--;
			bSomethingHappened = true;
		}
        
    }
    if (g_abKeyPressed[K_LEFT] && g_sChar.m_cLocation.X > 0)
    {
		if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X - 1) - (90 - mapSizeWidth)] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X--;
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_DOWN] && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
		if (map[(g_sChar.m_cLocation.Y + 1) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X) - (90 - mapSizeWidth)] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.Y++;
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_RIGHT] && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
		if (map[(g_sChar.m_cLocation.Y) - (25 - mapSizeHeight)][(g_sChar.m_cLocation.X + 1) - (90 - mapSizeWidth)] != (char)219)
		{
			//Beep(1440, 30);
			g_sChar.m_cLocation.X++;
			bSomethingHappened = true;
		}
    }
    if (g_abKeyPressed[K_SPACE])
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;
        bSomethingHappened = true;
    }

    if (bSomethingHappened)
    {
        // set the bounce time to some time in the future to prevent accidental triggers
        g_dBounceTime = g_dElapsedTime + 0.125; // 125ms should be enough
    }
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

void clearScreen()
{
    // Clears the buffer
    g_Console.clearBuffer(0000);
}

void renderSplashScreen()  // renders the splash screen
{	
	//Sends map info to be stored (so file only needs to open once)
	if (newMap)
	{
		newMap = false;
		loadMap(0);
	}
	//Print map in cpp functions
	printMap(mapSizeWidth, mapSizeHeight, false);
}

void renderGame()
{
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
	//Sends map info to be stored (so file only needs to open once)
	if (newMap)
	{
		newMap = false;
		loadMap(2);
	}
	//Print map in cpp functions
	printMap(mapSizeWidth, mapSizeHeight, false);
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)234, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());
}
void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderMainMenu()
{
	if (newMap)
	{
		newMap = false;
		loadMap(1);
	}
	//Print map in cpp functions
	printMap(mapSizeWidth, mapSizeHeight, true);

	//Start game if flag is true and hits enter key
	if (g_abKeyPressed[K_ENTER])
	{
		newMap = true;
		g_eGameState = S_GAME;// sets the state to start
	}
	
	// quits the game if player hits the escape key
	if (g_abKeyPressed[K_ESCAPE])
		g_bQuitGame = true;
}
