#include "console.h"
#include <cstdio>

// Set a screen buffer for us to write to before flushing it to the screen
HANDLE hScreenBuffer = INVALID_HANDLE_VALUE; 
CHAR_INFO* screenDataBuffer = 0;
extern COORD ConsoleSize;

void gotoXY(int x,int y)
{
	COORD c={x,y};
    gotoXY(c);
}

void gotoXY(COORD c)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void colour(WORD attrib)
{	
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hstdout, attrib );
		
}

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void cls( HANDLE hConsole )
{
    if (!hConsole)
        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
        dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
}
	
bool isKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}


void initConsole(COORD consoleSize, LPCSTR lpConsoleTitle)
{
    // Use the ascii version for the consoleTitle
    SetConsoleTitleA(lpConsoleTitle);
    SetConsoleCP(437);
    
    // set up screen buffer
    screenDataBuffer = new CHAR_INFO[consoleSize.X * consoleSize.Y];

    hScreenBuffer = CreateConsoleScreenBuffer( 
       GENERIC_READ |           // read/write access 
       GENERIC_WRITE, 
       FILE_SHARE_READ | 
       FILE_SHARE_WRITE,        // shared 
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 

    SetConsoleActiveScreenBuffer(hScreenBuffer); 
    // Sets the console size
    setConsoleSize(consoleSize.X, consoleSize.Y);
}

void shutDownConsole()
{
    delete [] screenDataBuffer;
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

CHAR_INFO* getScreenDataBuffer()
{
    return screenDataBuffer;
}

void flushBufferToConsole()
{
    COORD c = {0,0};
    SMALL_RECT WriteRegion = {0, 0, ConsoleSize.X-1, ConsoleSize.Y-1};
    // WriteConsoleOutputA for ASCII text
    WriteConsoleOutputA(hScreenBuffer, screenDataBuffer, ConsoleSize, c, &WriteRegion);
}

// sets the size of the console
void setConsoleSize(unsigned short consoleWidth, unsigned short consoleHeight)
{
    SMALL_RECT windowSize = {0, 0, consoleWidth-1, consoleHeight-1};
    COORD buffSize = {consoleWidth, consoleHeight};

    HANDLE hConsole = hScreenBuffer;//GetStdHandle( STD_OUTPUT_HANDLE );
    BOOL bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    PERR( bSuccess, "SetConsoleWindowInfo" );
    bSuccess = SetConsoleScreenBufferSize(hConsole, buffSize);
	PERR( bSuccess, "SetConsoleWindowInfo" );
}
void clearBuffer(WORD attribute)
{
    size_t buffSize = ConsoleSize.X * ConsoleSize.Y;
    for (size_t i = 0; i < buffSize; ++i)
    {
        screenDataBuffer[i].Char.AsciiChar = ' ';
        screenDataBuffer[i].Attributes = attribute;
    }
}
void writeToBuffer(COORD c, LPCSTR str, WORD attribute)
{    
    size_t index = c.X + ConsoleSize.X * c.Y;
    size_t length = strlen(str);
    for (size_t i = 0; i < length; ++i)
    {
        screenDataBuffer[index+i].Char.AsciiChar = *(str+i);
        screenDataBuffer[index+i].Attributes = attribute;
    }
}

void writeToBuffer(COORD c, std::string s, WORD attribute)
{
    writeToBuffer(c, s.c_str(), attribute);
}

void writeToBuffer(COORD c, char ch, WORD attribute)
{
    screenDataBuffer[c.X + ConsoleSize.X * c.Y].Char.AsciiChar = ch;
    screenDataBuffer[c.X + ConsoleSize.X * c.Y].Attributes = attribute;
}

void writeToConsole(const CHAR_INFO* lpBuffer)
{
    COORD c = {0,0};
    SMALL_RECT WriteRegion = {0, 0, ConsoleSize.X-1, ConsoleSize.Y-1};
    // WriteConsoleOutputA for ASCII text
    WriteConsoleOutputA(hScreenBuffer, screenDataBuffer, ConsoleSize, c, &WriteRegion);
}
