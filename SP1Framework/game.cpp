// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double	g_dElapsedTime;
double	g_dDeltaTime;
bool	g_abKeyPressed[K_COUNT];
COORD	g_cCharLocation;
COORD	g_cConsoleSize;

//--------------------------------------------------------------
// Purpose	: Initialisation function
// Input	: Void
// Output	: void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

	// set the name of your console window
    SetConsoleTitle(L"SP1 Framework");

    // Sets the console size, this is the biggest so far.
    setConsoleSize(79, 28);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    g_cConsoleSize.X = csbi.srWindow.Right + 1;
    g_cConsoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    g_cCharLocation.X = g_cConsoleSize.X / 2;
    g_cCharLocation.Y = g_cConsoleSize.Y / 2;

    g_dElapsedTime = 0.0;
}

//--------------------------------------------------------------
// Purpose	: Reset before exiting the program
// Input	: Void
// Output	: void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

//--------------------------------------------------------------
// Purpose	: Getting all the key press states
// Input	: Void
// Output	: void
//--------------------------------------------------------------
void getInput( void )
{    
    g_abKeyPressed[K_UP] = isKeyPressed(VK_UP);
    g_abKeyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    g_abKeyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    g_abKeyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    g_abKeyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

//--------------------------------------------------------------
// Purpose	: Update function
// Input	: dt = deltatime
// Output	: void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    // Updating the location of the character based on the key press
	// providing a beep sound whenver we shift the character
    if (g_abKeyPressed[K_UP] && g_cCharLocation.Y > 0)
    {
        Beep(1440, 30);
        g_cCharLocation.Y--; 
    }
    if (g_abKeyPressed[K_LEFT] && g_cCharLocation.X > 0)
    {
        Beep(1440, 30);
        g_cCharLocation.X--; 
    }
    if (g_abKeyPressed[K_DOWN] && g_cCharLocation.Y < g_cConsoleSize.Y - 1)
    {
        Beep(1440, 30);
        g_cCharLocation.Y++; 
    }
    if (g_abKeyPressed[K_RIGHT] && g_cCharLocation.X < g_cConsoleSize.X - 1)
    {
        Beep(1440, 30);
        g_cCharLocation.X++; 
    }

    // quits the game if player hits the escape key
    if (g_abKeyPressed[K_ESCAPE])
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose	: Render function is to update the console screen
// Input	: void
// Output	: void
//--------------------------------------------------------------
void render( void )
{
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
    std::cout << 1.0 / g_dDeltaTime << "fps" << std::endl;
  
    gotoXY(0, 0);
    colour(0x59);
    std::cout << g_dElapsedTime << "secs" << std::endl;

    // render character
    gotoXY(g_cCharLocation);
    colour(0x0C);
    std::cout << (char)1;
}
