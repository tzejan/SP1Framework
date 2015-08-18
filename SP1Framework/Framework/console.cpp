#include "console.h"
#include <cstdio>

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api) { if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__); }

//--------------------------------------------------------------
// Purpose  : Setting position of the console cursor
// Input    : Coord (x and y are short)
// Output   : Nil
//--------------------------------------------------------------
void gotoXY(COORD c)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

//--------------------------------------------------------------
// Purpose  : Setting position of the console cursor using int
// Input    : int, int
// Output   : Nil
//--------------------------------------------------------------
void gotoXY(int iX,int iY)
{
    COORD c = { iX, iY };
    gotoXY(c);
}

//--------------------------------------------------------------
// Purpose  : Setting colour of the console text
// Input    : WORD (2 bytes data type)
// Output   : Nil
//--------------------------------------------------------------
void colour(WORD wAttrib)
{    
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( hStdout, wAttrib );        
}

//--------------------------------------------------------------
// Purpose  : Clear Sreen
// Input    : Console handler
// Output   : Nil
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
// Purpose  : Check for key press status of specific key
// Input    : Key to check (Short)
// Output   : Nil
//--------------------------------------------------------------
bool isKeyPressed(unsigned short ushKey)
{
    return ((GetAsyncKeyState(ushKey) & 0x8001) != 0);
}

//=============================================================================
// Console object code follows
//=============================================================================
Console::Console(COORD consoleSize, LPCSTR lpConsoleTitle) : 
    screenDataBufferSize(consoleSize.X * consoleSize.Y)
{
    initConsole(consoleSize, lpConsoleTitle);
}

Console::Console(unsigned short consoleWidth, unsigned short consoleHeight, LPCSTR lpConsoleTitle) :
    screenDataBufferSize(consoleWidth * consoleHeight)
{
    COORD consoleSize = { consoleWidth, consoleHeight };
    initConsole(consoleSize, lpConsoleTitle);
}

Console::~Console()
{
    shutDownConsole();
}

void Console::initConsole(COORD consoleSize, LPCSTR lpConsoleTitle)
{
    // Use the ascii version for the consoleTitle
    SetConsoleTitleA(lpConsoleTitle);
    SetConsoleCP(437);
    
    // set up screen buffer    
    screenDataBuffer = new CHAR_INFO[screenDataBufferSize];

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
    this->consoleSize = consoleSize;
}

void Console::setConsoleTitle(LPCSTR lpConsoleTitle)
{
    SetConsoleTitleA(lpConsoleTitle);
}

void Console::setConsoleFont(SHORT width, SHORT height, LPCWSTR lpcwFontName)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof cfi;
    cfi.nFont = 0;
    cfi.dwFontSize.X = width;
    cfi.dwFontSize.Y = height;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, lpcwFontName);
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Console::shutDownConsole()
{
    delete [] screenDataBuffer;
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}


void Console::flushBufferToConsole()
{
    writeToConsole(screenDataBuffer);    
}

// sets the size of the console
void Console::setConsoleSize(unsigned short consoleWidth, unsigned short consoleHeight)
{
    SMALL_RECT windowSize = {0, 0, consoleWidth-1, consoleHeight-1};
    COORD buffSize = {consoleWidth, consoleHeight};

    HANDLE hConsole = hScreenBuffer;//GetStdHandle( STD_OUTPUT_HANDLE );
    BOOL bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
    PERR( bSuccess, "SetConsoleWindowInfo" );
    bSuccess = SetConsoleScreenBufferSize(hConsole, buffSize);
    PERR( bSuccess, "SetConsoleWindowInfo" );
}
void Console::clearBuffer(WORD attribute)
{
    for (size_t i = 0; i < screenDataBufferSize; ++i)
    {
        screenDataBuffer[i].Char.AsciiChar = ' ';
        screenDataBuffer[i].Attributes = attribute;
    }
}

void Console::writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attribute)
{
    size_t index = max(x + consoleSize.X * y, 0);
    size_t length = strlen(str);
    // if the length of the string exceeds the buffer size, we chop it off at the end
    length = min(screenDataBufferSize - index - 1, length);
    for (size_t i = 0; i < length; ++i)
    {
        screenDataBuffer[index+i].Char.AsciiChar = str[i];
        screenDataBuffer[index+i].Attributes = attribute;
    }
}

void Console::writeToBuffer(COORD c, LPCSTR str, WORD attribute)
{    
    writeToBuffer(c.X, c.Y, str, attribute);
}

void Console::writeToBuffer(SHORT x, SHORT y, std::string& s, WORD attribute)
{
    writeToBuffer(x, y, s.c_str(), attribute);
}

void Console::writeToBuffer(COORD c, std::string& s, WORD attribute)
{
    writeToBuffer(c.X, c.Y, s.c_str(), attribute);
}

void Console::writeToBuffer(SHORT x, SHORT y, char ch, WORD attribute)
{
    if (x < 0 || x > consoleSize.X || y < 0 || y > consoleSize.Y)
        return;
    screenDataBuffer[x + consoleSize.X * y].Char.AsciiChar = ch;
    screenDataBuffer[x + consoleSize.X * y].Attributes = attribute;
}

void Console::writeToBuffer(COORD c, char ch, WORD attribute)
{
    writeToBuffer(c.X, c.Y, ch, attribute);
}

void Console::writeToConsole(const CHAR_INFO* lpBuffer)
{
    COORD c = {0,0};
    SMALL_RECT WriteRegion = {0, 0, consoleSize.X-1, consoleSize.Y-1};
    // WriteConsoleOutputA for ASCII text
    WriteConsoleOutputA(hScreenBuffer, lpBuffer, consoleSize, c, &WriteRegion);
}
