// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>

double elapsedTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.
    charLocation.X = consoleSize.X / 2;
    charLocation.Y = consoleSize.Y / 2;
}

void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
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
    elapsedTime = dt;

    // Updating the location of the character based on the key press
    if (keyPressed[K_UP] && charLocation.Y > 0)
    {
        playGameSound(S_MOVE);
        charLocation.Y--; 
    }
    if (keyPressed[K_LEFT] && charLocation.X > 0)
    {
        playGameSound(S_MOVE);
        charLocation.X--; 
    }
    if (keyPressed[K_DOWN] && charLocation.Y < consoleSize.Y - 1)
    {
        playGameSound(S_MOVE);
        charLocation.Y++; 
    }
    if (keyPressed[K_RIGHT] && charLocation.X < consoleSize.X - 1)
    {
        playGameSound(S_MOVE);
        charLocation.X++; 
    }

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        g_quitGame = true;    
}

void render()
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
		gotoXY(3*i,i);
		colour(colors[i]);
		std::cout << "WOW";
	}

    // render time taken to calculate this frame
    gotoXY(70, 0);
    colour(0x1A);
    std::cout << 1.0 / elapsedTime << "fps" << std::endl;
    
    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;

    
}


void playGameSound(SoundType sound)
{
    switch (sound)
    {
        case S_MOVE: Beep(1440, 40);
                    break;
        case S_MUSIC : Beep(555, 40);
                    break;
    }
}

void playNote(char note) // play this note
{
    // not gonna happen
/*
Octave 0    1    2    3    4    5    6    7
Note
C     16   33   65  131  262  523 1046 2093
C#    17   35   69  139  277  554 1109 2217
D     18   37   73  147  294  587 1175 2349
D#    19   39   78  155  311  622 1244 2489
E     21   41   82  165  330  659 1328 2637
F     22   44   87  175  349  698 1397 2794
F#    23   46   92  185  370  740 1480 2960
G     24   49   98  196  392  784 1568 3136
G#    26   52  104  208  415  831 1661 3322
A     27   55  110  220  440  880 1760 3520
A#    29   58  116  233  466  932 1865 3729
B     31   62  123  245  494  988 1975 3951
*/
}