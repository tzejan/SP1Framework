#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <windows.h>
#include <string>

// SOON TO DEPRECATE FUNCTIONS

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

// FAST RENDERING TO CONSOLE FUNCTIONS

// sets the size of the console
// There is a certain size limitation to how big a console can be set.
void setConsoleSize(unsigned short consoleWidth, unsigned short consoleHeight);

//===================================================================================================
// The functions below sets up the screen buffer and writes to the console with this data

// Initializes the console for this size
void initConsole(COORD consoleSize, LPCSTR lpConsoleTitle=0);

void shutDownConsole();

CHAR_INFO* getScreenDataBuffer();

void flushBufferToConsole();
void clearBuffer(WORD attribute = 0x0F);

void writeToBuffer(COORD c, LPCSTR str, WORD attribute = 0x0F);
void writeToBuffer(COORD c, std::string s, WORD attribute = 0x0F);
void writeToBuffer(COORD c, char ch, WORD attribute = 0x0F);
void writeToConsole(const CHAR_INFO* lpBuffer);

#endif // _CONSOLE_H