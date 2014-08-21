// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include "Graphics.h"
#include "TableFlip.h"

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;
Graphics TableFlip;


void init()
{
    elapsedTime = 0.0;
}

void shutdown()
{

}

void getInput()
{    
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
    deltaTime = dt;

	updateTableFlip();

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
{
	drawTableFlip(&TableFlip);
	TableFlip.updateconsole();
}
