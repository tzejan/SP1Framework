// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// Console size, width by height
COORD ConsoleSize = {80, 25};

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];


// Game specific variables here
COORD charLocation;

void init()
{
    // Set precision for floating point output
    elapsedTime = 0.0;

    initConsole(ConsoleSize, "SP1 Framework");

    charLocation.X = ConsoleSize.X / 2;
    charLocation.Y = ConsoleSize.Y / 2;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    shutDownConsole();
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        //Beep(1440, 30);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        //Beep(1440, 30);
        charLocation.X--;
    }
    if (keyPressed[K_DOWN] && charLocation.Y < ConsoleSize.Y - 1)
    {
        //Beep(1440, 30);
        charLocation.Y++;
    }
    if (keyPressed[K_RIGHT] && charLocation.X < ConsoleSize.X - 1)
    {
        //Beep(1440, 30);
        charLocation.X++;
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{    
    // Clears the buffer with this colour attribute
    clearBuffer(0x1F);

    // Set up sample colours, and output shadings
    const WORD colors[] =   {
	                        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	                        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
	                        };
	
    COORD c;
	for (int i = 0; i < 12; ++i)
	{
		c.X = 5*i;
        c.Y = i+1;
		colour(colors[i]);
		writeToBuffer(c, " °±²Û", colors[i]);
	}

    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / deltaTime << "fps";
    c.X = ConsoleSize.X-9;
    c.Y = 0;
    writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << elapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    writeToBuffer(c, ss.str(), 0x59);


    // Draw the location of the character
    writeToBuffer(charLocation, (char)1, 0x0C);

    
    // Writes the buffer to the console, hence you will see what you have written
    flushBufferToConsole();
}
