// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
bool keys[K_COUNT];

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keys[K_UP] = GetAsyncKeyState(VK_UP) & 0x8000;
    keys[K_DOWN] = GetAsyncKeyState(VK_DOWN) & 0x8000;
    keys[K_ESCAPE] = GetAsyncKeyState(VK_ESCAPE) & 0x8000;        
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
    std::cout << 1.0 / elapsedTime << "fps" << std::endl;
    
    gotoxy(20, 20);
    colour(0x7C);
    if (keys[K_UP])
    {
        std::cout << "UP was pressed";
    }
    if (keys[K_DOWN])
    {
        std::cout << "DOWN was pressed";
    }

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
bool update(double dt)
{
    elapsedTime = dt;


    if (keys[K_ESCAPE])
        g_quitGame = true;

    return g_quitGame; 
}