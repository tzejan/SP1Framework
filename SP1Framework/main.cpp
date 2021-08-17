// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"

CStopWatch g_Timer;                            // Timer function to keep track of time and the frame rate
bool g_bQuitGame = false;                    // Set to true if you want to quit the game
const unsigned char gc_ucFPS = 100;                // FPS of this game
const unsigned int gc_uFrameTime = 1000 / gc_ucFPS;    // time for each frame

bool gO = false;

//main loop declaration
void mainLoop( void );

// TODO:
// Bug in waitUntil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

// main function - starting function
// You should not be modifying this unless you know what you are doing
int main( void )
{
    init();      // initialize your variables
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
    
    return 0;
}

//--------------------------------------------------------------
// Purpose  : This main loop calls functions to get input, 
//            update and render the game at a specific frame rate
//            You should not be modifying this unless you know what you are doing.
// Input    : void
// Output   : void
//--------------------------------------------------------------
void mainLoop( void )
{
    g_Timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (!g_bQuitGame)      // run this loop until user wants to quit 
    {   

        update(g_Timer.getElapsedTime());
        getInput();
        render2();
        update(g_Timer.getElapsedTime());
        g_Timer.waitUntil(gc_uFrameTime);
        if (renderMenu() == 1)
        {
            while (!gO)
            {
                CStopWatch h_Timer;
                h_Timer.startTimer();
                getInput();
                render();
                update(h_Timer.getElapsedTime());
            }
        }
        else if (renderMenu() == 2)
        {
            while (!gO)
            {
                CStopWatch h_Timer;
                h_Timer.startTimer();
                getInput();
                render3();
                update(h_Timer.getElapsedTime());
            }
        }
        else if (renderMenu() == 3)
        {
            g_bQuitGame = true;
        }
    }    
}
