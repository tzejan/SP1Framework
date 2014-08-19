#include "console.h"
#include <cstdio>


HANDLE hNewScreenBuffer; 

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

// sets the size of the console
void setConsoleSize(unsigned short x, unsigned short y)
{
    SMALL_RECT windowSize = {0, 0, x, y};

    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    bool bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
	PERR( bSuccess, "SetConsoleWindowInfo" );
}

void writeToConsole(unsigned short x, unsigned short y, LPCWSTR str, WORD attribute)
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD c = {x,y};
    DWORD charsWritten;
    CHAR_INFO lpBuffer[30]; 
    COORD buffSize = {30,30};
    WriteConsoleOutputCharacter(hConsole, str, lstrlen(str), c, &charsWritten);
    //WriteConsoleOutput(hConsole, &lpBuffer, buffSize, c, &attribute, lstrlen(str), c, &charsWritten);

}

void writeToConsole(const CHAR_INFO* lpBuffer)
{
    //HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD buffSize = {80,25};
    COORD c = {0,0};
    SMALL_RECT WriteRegion = {0, 0, 79, 24};
    // WriteConsoleOutputA for ASCII text
    WriteConsoleOutputA(hNewScreenBuffer, lpBuffer, buffSize, c, &WriteRegion);
}

//http://www.cplusplus.com/forum/windows/121444/
//
// write to  a CHAR_INFO buffer, CHAR_INFO contains the actual character and the attributes of the character
// then wrote this buffer to the console output.
//

void writing()
{
     HANDLE hStdout, hNewScreenBuffer; 
    SMALL_RECT srctReadRect; 
    SMALL_RECT srctWriteRect; 
    CHAR_INFO chiBuffer[160]; // [2][80]; 
    COORD coordBufSize; 
    COORD coordBufCoord; 
    BOOL fSuccess; 
 
    // Get a handle to the STDOUT screen buffer to copy from and 
    // create a new screen buffer to copy to. 
 
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
    hNewScreenBuffer = CreateConsoleScreenBuffer( 
       GENERIC_READ |           // read/write access 
       GENERIC_WRITE, 
       FILE_SHARE_READ | 
       FILE_SHARE_WRITE,        // shared 
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 
    if (hStdout == INVALID_HANDLE_VALUE || 
            hNewScreenBuffer == INVALID_HANDLE_VALUE) 
    {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError()); 
        return;
    }
 
    // Make the new screen buffer the active screen buffer. 
 
    if (! SetConsoleActiveScreenBuffer(hNewScreenBuffer) ) 
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError()); 
        return;
    }
 
    // Set the source rectangle. 
 
    srctReadRect.Top = 0;    // top left: row 0, col 0 
    srctReadRect.Left = 0; 
    srctReadRect.Bottom = 1; // bot. right: row 1, col 79 
    srctReadRect.Right = 79; 
 
    // The temporary buffer size is 2 rows x 80 columns. 
 
    coordBufSize.Y = 2; 
    coordBufSize.X = 80; 
 
    // The top left destination cell of the temporary buffer is 
    // row 0, col 0. 
 
    coordBufCoord.X = 0; 
    coordBufCoord.Y = 0; 
 
    // Copy the block from the screen buffer to the temp. buffer. 
 
    fSuccess = ReadConsoleOutput( 
       hStdout,        // screen buffer to read from 
       chiBuffer,      // buffer to copy into 
       coordBufSize,   // col-row size of chiBuffer 
       coordBufCoord,  // top left dest. cell in chiBuffer 
       &srctReadRect); // screen buffer source rectangle 
    if (! fSuccess) 
    {
        printf("ReadConsoleOutput failed - (%d)\n", GetLastError()); 
        return;
    }
 
    // Set the destination rectangle. 
 
    srctWriteRect.Top = 10;    // top lt: row 10, col 0 
    srctWriteRect.Left = 0; 
    srctWriteRect.Bottom = 11; // bot. rt: row 11, col 79 
    srctWriteRect.Right = 79; 
 
    // Copy from the temporary buffer to the new screen buffer. 
 
    fSuccess = WriteConsoleOutput( 
        hNewScreenBuffer, // screen buffer to write to 
        chiBuffer,        // buffer to copy from 
        coordBufSize,     // col-row size of chiBuffer 
        coordBufCoord,    // top left src cell in chiBuffer 
        &srctWriteRect);  // dest. screen buffer rectangle 
    if (! fSuccess) 
    {
        printf("WriteConsoleOutput failed - (%d)\n", GetLastError()); 
        return;
    }
    Sleep(5000); 
 
    // Restore the original active screen buffer. 
 
    if (! SetConsoleActiveScreenBuffer(hStdout)) 
    {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError()); 
        return;
    }
}