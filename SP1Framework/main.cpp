// This is the main file to hold everthing together
/*
Idea on how to have the timer for the customers:
when customer is created using a pointer, make another pointer (timePtr maybe) = new CStopWatch,
and have it count up till 10 seconds. After 10 seconds over, call the function entranceWaiting.
Then make a function to show the item the customer is buying and how much the customer is buying.
When the timer reaches 30 seconds (because 20 seconds of waiting at shelf)
or when the customers order is satisfied, delete the customer,
set it to nullptr, do the same for the stopwatch. Make function to story hidden money
(either in player or in customer)
*/

#include "Framework\timer.h"
#include "game.h"
#include "Box.h"

CStopWatch g_Timer;                            // Timer function to keep track of time and the frame rate
bool g_bQuitGame = false;                    // Set to true if you want to quit the game
const unsigned char gc_ucFPS = 40;                // FPS of this game
const unsigned int gc_uFrameTime = 1000 / gc_ucFPS;    // time for each frame

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
        getInput();                         // get keyboard input
        update(g_Timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_Timer.waitUntil(gc_uFrameTime);   // Frame rate limiter. Limits each frame to a specified time in ms.      
    }    
}
//test