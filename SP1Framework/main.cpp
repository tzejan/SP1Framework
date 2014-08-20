// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
bool PlayGame = false;
const unsigned char FPS = 8; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
void mainLoop();

// TODO:
// Bug in waitUntil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

int main()
{
	init();      // initialize your variables
	/*title();*/
	mainLoop(); 
    shutdown();  // do clean up, if any. free memory.
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{

    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_quitGame)      // run this loop until user wants to quit 
	{        
        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}    
}
