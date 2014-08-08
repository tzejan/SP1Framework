// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "game.h"


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 30; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

void mainLoop();
// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.
// Get key state
// structs



int main()
{
	init();      // initialize your variables
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
	
	return 0;
}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
    g_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
    while (true)                 // run this loop until user wants to quit 
	{        
        getInput();              // get keyboard input
        if (update(g_timer.getElapsedTime())) // update the game and see if the user decides to quit the game
            return;
        render();                // render the graphics output to screen
        g_timer.waitUntil(frameTime);   // Frame rate limiter. Limits each frame to a specified time in ms.      
	}
    
}
/*

void cursor()
{
    int x = 5; int y = 6;
    COORD pos = {x, y};
    HANDLE hConsole_c = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);    
    SetConsoleActiveScreenBuffer(hConsole_c);
    //HANDLE hConsole_c = GetStdHandle(STD_OUTPUT_HANDLE);
    char *str = "Some Text";    
    wchar_t wstr[20]; 
    DWORD len = strlen(str); 
    size_t converted = 0;
    mbstowcs_s(&converted, wstr, 20, str, len);
    
    DWORD dwBytesWritten = 0;
    WriteConsoleOutputCharacter(hConsole_c, wstr, len, pos, &dwBytesWritten);
    std::cout << dwBytesWritten;
    Sleep(5000); 
    CloseHandle(hConsole_c);
}


void example(void) 
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
    int x = 5; int y = 6;
    COORD pos = {x, y};
    char *str = "Some Text";
    wchar_t wstr[20]; 
    DWORD len = strlen(str); 
    size_t converted = 0;
    mbstowcs_s(&converted, wstr, 20, str, len);
 
    
    //fSuccess = WriteConsoleOutput( 
    //    hNewScreenBuffer, // screen buffer to write to 
    //    chiBuffer,        // buffer to copy from 
    //    coordBufSize,     // col-row size of chiBuffer 
    //    coordBufCoord,    // top left src cell in chiBuffer 
    //    &srctWriteRect);  // dest. screen buffer rectangle 
        
    DWORD dwBytesWritten = 0;
    fSuccess = WriteConsoleOutputCharacter(hNewScreenBuffer, wstr, len, pos, &dwBytesWritten);
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

*/