#include "console.h"
#include <cstdio>

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api) { if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__); }

//--------------------------------------------------------------
// Purpose	: Setting position of the console cursor
// Input	: Coord (x and y are short)
// Output	: Nil
//--------------------------------------------------------------
void gotoXY(COORD c)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

//--------------------------------------------------------------
// Purpose	: Setting position of the console cursor using int
// Input	: Int, Int
// Output	: Nil
//--------------------------------------------------------------
void gotoXY(int iX,int iY)
{
	COORD c={ iX,iY };
    gotoXY(c);
}

//--------------------------------------------------------------
// Purpose	: Setting colour of the console text
// Input	: WORD (2 bytes data type)
// Output	: Nil
//--------------------------------------------------------------
void colour(WORD wAttrib)
{	
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hStdout, wAttrib );
		
}

//--------------------------------------------------------------
// Purpose	: Clear Sreen
// Input	: Console handler
// Output	: Nil
//--------------------------------------------------------------
void cls( HANDLE hConsole )
{
    if (!hConsole)
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
	
//--------------------------------------------------------------
// Purpose	: Check for key press status of specific key
// Input	: Key to check (Short)
// Output	: Nil
//--------------------------------------------------------------
bool isKeyPressed(unsigned short ushKey)
{
	// to know more about GetAsyncKeyState
	// goto https://msdn.microsoft.com/en-us/library/windows/desktop/ms646293(v=vs.85).aspx
    return ((GetAsyncKeyState(ushKey) & 0x8001) != 0);
}

//--------------------------------------------------------------
// Purpose	: Set Console Size 
// Input	: X and Y sizing in short
// Output	: Nil
//--------------------------------------------------------------
void setConsoleSize(unsigned short ushX, unsigned short ushY)
{
    SMALL_RECT windowSize = {0, 0, ushX, ushY};

    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    bool bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	PERR( bSuccess, "SetConsoleWindowInfo" );
}