// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>


void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(5);
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{
    unsigned short keyState = GetAsyncKeyState(VK_ESCAPE);
    if (keyState)
    {
        std::cout << "Escape was pressed" << std::endl;
        g_continueGame = true;
    }

        
}
void render()
{
    // clear screen
    colour(0x0F);
    cls();

    //render the game

    // render time taken to calculate this frame
    gotoxy(70, 0);
    colour(0x1A);
    timer.stopTimer();
    std::cout << timer.getElapsedTime() << "s" << std::endl;
    

    return;
    const WORD colors[] =
	{
	0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	};
	
	for (int i = 0; i < 12; ++i)
	{
		gotoxy(3*i,2*i);
		colour(colors[i]);
		std::cout << "\t\t\tWords lalala\t\t\t\n";
	}

	
    
    std::cout << char(223);
}
bool update()
{
    return g_continueGame; 
}