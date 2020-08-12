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
// Purpose  : Clear Screen
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
	m_u32ScreenDataBufferSize(consoleSize.X * consoleSize.Y),
    m_pfKeyboardHandler(0),
    m_pfMouseHandler(0)
{
    initConsole(consoleSize, lpConsoleTitle);
}

Console::Console(unsigned short consoleWidth, unsigned short consoleHeight, LPCSTR lpConsoleTitle) :
    m_u32ScreenDataBufferSize(consoleWidth * consoleHeight),
    m_pfKeyboardHandler(0),
    m_pfMouseHandler(0)
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
	this->m_cConsoleSize = consoleSize;
    // Use the ascii version for the consoleTitle
    SetConsoleTitleA(lpConsoleTitle);
    SetConsoleCP(437);
    
    // set up screen buffer    
	m_ciScreenDataBuffer = new CHAR_INFO[m_u32ScreenDataBufferSize];

    m_hScreenBuffer = CreateConsoleScreenBuffer( 
       GENERIC_READ |           // read/write access 
       GENERIC_WRITE, 
       FILE_SHARE_READ | 
       FILE_SHARE_WRITE,        // shared 
       NULL,                    // default security attributes 
       CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
       NULL);                   // reserved; must be NULL 

	m_cMaxConsoleSize = GetLargestConsoleWindowSize(m_hScreenBuffer);

	// Sets the console size
	setConsoleWindowSize();
    SetConsoleActiveScreenBuffer(m_hScreenBuffer);
    m_topleft_c = { 0, 0 };
    m_writeRegion = { 0, 0, m_cConsoleSize.X - 1, m_cConsoleSize.Y - 1 };

    // initialize the input console
    initInput();
}

void Console::initInput()
{
    BOOL bSuccess;

    // Get the standard input handle.
    m_hStdin = GetStdHandle(STD_INPUT_HANDLE);
    bSuccess = m_hStdin != INVALID_HANDLE_VALUE;
    PERR(bSuccess, "GetStdHandle");

    // Save the current input mode, to be restored on exit. 

    bSuccess = GetConsoleMode(m_hStdin, &m_fdwSaveOldMode);
    PERR(bSuccess, "GetConsoleMode");

    // Enable the window and mouse input events. 

    DWORD fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    fdwMode &= ~ENABLE_QUICK_EDIT_MODE;
    bSuccess = SetConsoleMode(m_hStdin, fdwMode | ENABLE_EXTENDED_FLAGS);
    PERR(bSuccess, "SetConsoleMode");
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
	delete [] m_ciScreenDataBuffer;
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));

    // restore input 
    SetConsoleMode(m_hStdin, m_fdwSaveOldMode | ENABLE_EXTENDED_FLAGS);
}


void Console::flushBufferToConsole()
{
	writeToConsole(m_ciScreenDataBuffer);    
}

// sets the size of the console
void Console::setConsoleWindowSize()
{
	SMALL_RECT windowSize = {0, 0, m_cConsoleSize.X-1, m_cConsoleSize.Y-1};
    COORD buffSize = {m_cConsoleSize.X, m_cConsoleSize.Y};

    HANDLE hConsole = m_hScreenBuffer;//GetStdHandle( STD_OUTPUT_HANDLE );

	BOOL bSuccess;

	CONSOLE_SCREEN_BUFFER_INFO csbi; // Hold Current Console Buffer Info 
	bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
	PERR( bSuccess, "GetConsoleScreenBufferInfo" );

	// If the Current Buffer is Larger than what we want, Resize the 
	// Console Window First, then the Buffer 
	if( (DWORD)csbi.dwSize.X * csbi.dwSize.Y > (DWORD) m_cConsoleSize.X * m_cConsoleSize.Y)
	{
		bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);    
		PERR( bSuccess, "SetConsoleWindowInfo" );
		bSuccess = SetConsoleScreenBufferSize(hConsole, buffSize);
		PERR( bSuccess, "SetConsoleScreenBufferSize" );
	}
	// If the Current Buffer is Smaller than what we want, Resize the 
	// Buffer First, then the Console Window 
	else
	{	
		bSuccess = SetConsoleScreenBufferSize(hConsole, buffSize);
		PERR( bSuccess, "SetConsoleScreenBufferSize" );
		bSuccess = SetConsoleWindowInfo(hConsole, TRUE, &windowSize);    
		PERR( bSuccess, "SetConsoleWindowInfo" );
	}
}
void Console::clearBuffer(WORD attribute)
{
    CHAR_INFO clear = { ' ', attribute };
	for (size_t i = 0; i < m_u32ScreenDataBufferSize; ++i)
    {
        m_ciScreenDataBuffer[i] = clear;
    }
}

void Console::writeToBuffer(SHORT x, SHORT y, LPCSTR str, WORD attribute, SHORT length)
{
	size_t index = max(x + m_cConsoleSize.X * y, 0);
    size_t str_idx = 0;
    // if the length of the string exceeds the buffer size, we chop it off at the end
    while (index < m_u32ScreenDataBufferSize && str[str_idx] != 0 && str_idx < length)
    {
        m_ciScreenDataBuffer[index].Char.AsciiChar = str[str_idx];
        m_ciScreenDataBuffer[index].Attributes = attribute;
        ++index;
        ++str_idx;
    }
}

void Console::writeToBuffer(COORD c, LPCSTR str, WORD attribute, SHORT length)
{    
    writeToBuffer(c.X, c.Y, str, attribute, length);
}

void Console::writeToBuffer(SHORT x, SHORT y, std::string& s, WORD attribute, SHORT length)
{
    writeToBuffer(x, y, s.c_str(), attribute, length);
}

void Console::writeToBuffer(COORD c, std::string& s, WORD attribute, SHORT length)
{
    writeToBuffer(c.X, c.Y, s.c_str(), attribute, length);
}

void Console::writeToBuffer(SHORT x, SHORT y, char ch, WORD attribute)
{
	if (x < 0 || x >= m_cConsoleSize.X || y < 0 || y >= m_cConsoleSize.Y)
        return;
	m_ciScreenDataBuffer[x + m_cConsoleSize.X * y].Char.AsciiChar = ch;
	m_ciScreenDataBuffer[x + m_cConsoleSize.X * y].Attributes = attribute;
}

void Console::writeToBuffer(COORD c, char ch, WORD attribute)
{
    writeToBuffer(c.X, c.Y, ch, attribute);
}

void Console::writeToConsole(const CHAR_INFO* lpBuffer)
{	
    // WriteConsoleOutputA for ASCII text
    WriteConsoleOutputA(m_hScreenBuffer, lpBuffer, m_cConsoleSize, m_topleft_c, &m_writeRegion);
}

void Console::readConsoleInput()
{
    DWORD numInputEvents;
    BOOL bSuccess;

    bSuccess = GetNumberOfConsoleInputEvents(m_hStdin, &numInputEvents);
    PERR(bSuccess, "GetNumberOfConsoleInputEvents");

    if (numInputEvents == 0)
        return;

    bSuccess = ReadConsoleInputA(
        m_hStdin,           // input buffer handle 
        m_irInBuf,          // buffer to read into 
        INPUT_BUFFER_SIZE,  // size of read buffer 
        &numInputEvents);   // number of records read 
    PERR(bSuccess, "ReadConsoleInput");

    // Dispatch the events to the appropriate handler. 

    for (int i = 0; i < numInputEvents; i++)
    {
        switch (m_irInBuf[i].EventType)
        {
        case KEY_EVENT: // keyboard input 
            if (m_pfKeyboardHandler) m_pfKeyboardHandler(m_irInBuf[i].Event.KeyEvent);
            break;

        case MOUSE_EVENT: // mouse input 
            if (m_pfMouseHandler) m_pfMouseHandler(m_irInBuf[i].Event.MouseEvent);
            break;        

        case FOCUS_EVENT:  // disregard focus events 

        case MENU_EVENT:   // disregard menu events 
            break;

        default:
            PERR(false, "Unknown event type");
            break;
        }
    }
}

void Console::setKeyboardHandler(void(*pfKeyboardHandler)(const KEY_EVENT_RECORD&))
{
    m_pfKeyboardHandler = pfKeyboardHandler;
}
void Console::setMouseHandler(void(*pfMouseHandler)(const MOUSE_EVENT_RECORD&))
{
    m_pfMouseHandler = pfMouseHandler;
}