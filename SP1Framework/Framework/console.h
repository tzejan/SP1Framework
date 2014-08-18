#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <windows.h>

// Go to a specific coordinate in the console
// Top left is origin (0,0), consoles usually have a width of 80 and height of 40
void gotoXY(int x,int y);
void gotoXY(COORD c);

// Sets the test and background to be of a specific colour
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes

// FOREGROUND_BLUE		Text color contains blue.
// FOREGROUND_GREEN		Text color contains green.
// FOREGROUND_RED		Text color contains red.
// FOREGROUND_INTENSITY	Text color is intensified.
// BACKGROUND_BLUE		Background color contains blue.
// BACKGROUND_GREEN		Background color contains green.
// BACKGROUND_RED		Background color contains red.
// BACKGROUND_INTENSITY	Background color is intensified.
void colour(WORD attrib);

// Clears the screen for this console handle
// If no console handle is supplied, then we take the STDOUTPUT console
void cls( HANDLE hConsole = 0);

bool isKeyPressed(unsigned short key);

// sets the size of the console
// There is a certain size limitation to how big a console can be set.
void setConsoleSize(unsigned short x, unsigned short y);

#endif // _CONSOLE_H