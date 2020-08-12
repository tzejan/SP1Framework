#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <windows.h>
#include <string>

//=============================================================================
// Slower write to screen functions
// Left here for posterity's sake to see how it was done
//=============================================================================

// Go to a specific coordinate in the console
// Top left is origin (0,0), consoles usually have a width of 80 and height of 40
void gotoXY(int x,int y);
void gotoXY(COORD c);

// Sets the test and background to be of a specific colour
// http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088(v=vs.85).aspx#_win32_character_attributes

// Bit positions and their color representations
// Bit 0 - FOREGROUND_BLUE          Text color contains blue.
// Bit 1 - FOREGROUND_GREEN         Text color contains green.
// Bit 2 - FOREGROUND_RED           Text color contains red.
// Bit 3 - FOREGROUND_INTENSITY     Text color is intensified.
// Bit 4 - BACKGROUND_BLUE          Background color contains blue.
// Bit 5 - BACKGROUND_GREEN         Background color contains green.
// Bit 6 - BACKGROUND_RED           Background color contains red.
// Bit 7 - BACKGROUND_INTENSITY     Background color is intensified.
void colour(WORD attrib);


// Clears the screen for this console handle
// If no console handle is supplied, then we take the STDOUTPUT console
void cls( HANDLE hConsole = 0);

//=============================================================================
// Console input function
//=============================================================================
// function to check if a key is pressed since the last call
bool isKeyPressed(unsigned short ushKkey);

//=============================================================================
// FAST RENDERING TO CONSOLE Object
//=============================================================================
class Console
{
    public:
        // Constructors, sets the console size and title.
        Console(COORD consoleSize, LPCSTR lpConsoleTitle = 0);
        Console(unsigned short consoleWidth, unsigned short consoleHeight, LPCSTR lpConsoleTitle = 0);
        ~Console();
        
        //===================================================================================================
        // The functions below sets up the screen buffer and writes to the console with this data
		COORD getConsoleSize() { return m_cConsoleSize; };  // Gets the console size
		COORD getMaxConsoleSize() { return m_cMaxConsoleSize; };  // Gets the maximum allowable console size
        void setConsoleTitle(LPCSTR lpConsoleTitle); // sets the console title
        void setConsoleFont(SHORT width, SHORT height, LPCWSTR lpcwFontName); // sets the console font
        void flushBufferToConsole(); // writes the contents of the buffer to the screen
        void clearBuffer(WORD attribute = 0x0F); // clears the screen with this colour

        // writeToBuffer takes in a c-style string, c++ string, or a char
        // You will need to provide the coordinate to place the leftmost character
        void writeToBuffer(COORD c, LPCSTR str, WORD attribute = 0x0F, SHORT length = 32767);
        void writeToBuffer(COORD c, std::string& s, WORD attribute = 0x0F, SHORT length = 32767);
        void writeToBuffer(COORD c, char ch, WORD attribute = 0x0F);
        void writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attribute = 0x0F, SHORT length = 32767);
        void writeToBuffer(SHORT x, SHORT y, std::string& s, WORD attribute = 0x0F, SHORT length = 32767);
        void writeToBuffer(SHORT x, SHORT y, char ch, WORD attribute = 0x0F);

        // These functions are for handling the console input, including mouse
        void readConsoleInput();
        void setKeyboardHandler(void (*pfKeyboardHandler)(const KEY_EVENT_RECORD&));
        void setMouseHandler(void(*pfMouseHandler)(const MOUSE_EVENT_RECORD&));
        
        //===================================================================================================
        // These are for your eyes only, don't bother to try to call the following functions.
    private:
        // Set a screen buffer for us to write to before flushing it to the screen
        HANDLE m_hScreenBuffer;
        CHAR_INFO* m_ciScreenDataBuffer;
        COORD m_cConsoleSize;
		COORD m_cMaxConsoleSize; // maximum console size
        const UINT32 m_u32ScreenDataBufferSize;
        COORD m_topleft_c;
        SMALL_RECT m_writeRegion;

        // for input
        HANDLE m_hStdin;        // standard input handler
        DWORD m_fdwSaveOldMode; // old mode for console input, for restoring input modes
        const static unsigned char INPUT_BUFFER_SIZE = 128;
        INPUT_RECORD m_irInBuf[INPUT_BUFFER_SIZE];

        // Handlers for Keyboard and mouse events
        void (*m_pfKeyboardHandler)(const KEY_EVENT_RECORD&);
        void (*m_pfMouseHandler)(const MOUSE_EVENT_RECORD&);

        //===================================================================================================
        // Private functions.

        // sets the size of the console
        // There is a certain size limitation to how big a console can be set.
        void setConsoleWindowSize();
        // Initializes the console for this size
        void initConsole(COORD consoleSize, LPCSTR lpConsoleTitle = 0);
        void writeToConsole(const CHAR_INFO* lpBuffer);
        void initInput();

        void shutDownConsole();
};

#endif // _CONSOLE_H
