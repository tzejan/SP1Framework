#include "Framework\timer.h"
#include "game.h"
#include <iostream>

CStopWatch g_Timer;                            // Timer function to keep track of time and the frame rate
bool g_bQuitGame = false;                    // Set to true if you want to quit the game
const unsigned char gc_ucFPS = 100;                // FPS of this game
const unsigned int gc_uFrameTime = 1000 / gc_ucFPS;    // time for each frame
using namespace std;
void mainLoop( void );

int main( void )
{
    init();     
    mainLoop(); 
    shutdown(); 
    
    return 0;
}

void mainLoop( void )
{
    g_Timer.startTimer(); 
    while (!g_bQuitGame)    
    {        
        getInput();                        
        update(g_Timer.getElapsedTime());  
        render();                          
        g_Timer.waitUntil(gc_uFrameTime);      
    }    
}
