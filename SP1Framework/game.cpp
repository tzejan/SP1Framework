// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include<stdio.h> 
using namespace std;
#include "Bullet.h"
double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(80, 25, "SP1 Framework");

Bullet* Amount_ofbullet[256] = { nullptr,};

void CheckAndUpdate()
{
    for (int i = 0; i < 256; i++)
    {
        if (Amount_ofbullet[i] != nullptr)
        {
            Amount_ofbullet[i]->UpdateXandY(g_Console);
            if ( (Amount_ofbullet[i]->x > 79) && (Amount_ofbullet[i]->x < 0) && (Amount_ofbullet[i]->y > 24) && (Amount_ofbullet[i]->y < 0) )
            {
                delete Amount_ofbullet[i];
                Amount_ofbullet[i] = nullptr;
            }
        }
    }

}

void MakesBullet()
{
    for (int i = 0; i < 256; i++)
    {
        if (Amount_ofbullet[i] == nullptr)
        {
            Amount_ofbullet[i] = new Bullet(g_sChar, g_mouseEvent);
            return;
        }
    }
    for (int i = 0; i < 256; i++) //pushes 
    {
        if (i + 1 >= 256)
        {
            Amount_ofbullet[i] = nullptr;
        }
        else
        {
            Amount_ofbullet[i + 1] = Amount_ofbullet[i];
        }
    }
}

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y / 2;
    g_sChar.m_bActive = true;
    // sets the width, height and the font name to use in the console
    g_Console.setConsoleFont(0, 16, L"Consolas");

    // remember to set your keyboard handler, so that your functions can be notified of input events
    g_Console.setKeyboardHandler(keyboardHandler);
    g_Console.setMouseHandler(mouseHandler);
}

//--------------------------------------------------------------
// Purpose  : Reset before exiting the program
//            Do your clean up of memory here
//            This is called once just before the game exits
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void shutdown( void )
{
    // Reset to white text on black background
    colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    g_Console.clearBuffer();
}

//--------------------------------------------------------------
// Purpose  : Get all the console input events
//            This function sets up the keyboard and mouse input from the console.
//            We will need to reset all the keyboard status, because no events will be sent if no keys are pressed.
//
//            Remember to set the handlers for keyboard and mouse events.
//            The function prototype of the handler is a function that takes in a const reference to the event struct
//            and returns nothing. 
//            void pfKeyboardHandler(const KEY_EVENT_RECORD&);
//            void pfMouseHandlerconst MOUSE_EVENT_RECORD&);
// Input    : Void
// Output   : void
//--------------------------------------------------------------
void getInput( void )
{
    // resets all the keyboard events
    memset(g_skKeyEvent, 0, K_COUNT * sizeof(*g_skKeyEvent));
    // then call the console to detect input from user
    g_Console.readConsoleInput();    
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the keyboard input. Whenever there is a keyboard event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            The KEY_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any keyboard event in the Splashscreen state
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent - reference to a key event struct
// Output   : void
//--------------------------------------------------------------
void keyboardHandler(const KEY_EVENT_RECORD& keyboardEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayKBHandler(keyboardEvent); // handle gameplay keyboard event 
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the handler for the mouse input. Whenever there is a mouse event, this function will be called.
//            Ideally, you should pass the key event to a specific function to handle the event.
//            This is because in some states, some keys would be disabled. Hence, to reduce your code complexity, 
//            it would be wise to split your keyboard input handlers separately.
//            
//            For the mouse event, if the mouse is not moved, no event will be sent, hence you should not reset the mouse status.
//            However, if the mouse goes out of the window, you would not be able to know either. 
//
//            The MOUSE_EVENT_RECORD struct has more attributes that you can use, if you are adventurous enough.
//
//            In this case, we are not handling any mouse event in the Splashscreen state
//            
// Input    : const MOUSE_EVENT_RECORD& mouseEvent - reference to a mouse event struct
// Output   : void
//--------------------------------------------------------------
void mouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{    
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: // don't handle anything for the splash screen
        break;
    case S_GAME: gameplayMouseHandler(mouseEvent); // handle gameplay mouse event
        break;
    }
}

//--------------------------------------------------------------
// Purpose  : This is the keyboard handler in the game state. Whenever there is a keyboard event in the game state, this function will be called.
//            
//            Add more keys to the enum in game.h if you need to detect more keys
//            To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
//            For Alphanumeric keys, the values are their ascii values (uppercase).
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayKBHandler(const KEY_EVENT_RECORD& keyboardEvent)
{
    // here, we map the key to our enums
    EKEYS key = K_COUNT;
    switch (keyboardEvent.wVirtualKeyCode)
    {
    case VK_UP: key = K_UP; break;
    case VK_DOWN: key = K_DOWN; break;
    case VK_LEFT: key = K_LEFT; break; 
    case VK_RIGHT: key = K_RIGHT; break; 
    case VK_SPACE: key = K_SPACE; break;
    case VK_ESCAPE: key = K_ESCAPE; break; 
    }
    // a key pressed event would be one with bKeyDown == true
    // a key released event would be one with bKeyDown == false
    // if no key is pressed, no event would be fired.
    // so we are tracking if a key is either pressed, or released
    if (key != K_COUNT)
    {
        g_skKeyEvent[key].keyDown = keyboardEvent.bKeyDown;
        g_skKeyEvent[key].keyReleased = !keyboardEvent.bKeyDown;
    }    
}

//--------------------------------------------------------------
// Purpose  : This is the mouse handler in the game state. Whenever there is a mouse event in the game state, this function will be called.
//            
//            If mouse clicks are detected, the corresponding bit for that mouse button will be set.
//            mouse wheel, 
//            
// Input    : const KEY_EVENT_RECORD& keyboardEvent
// Output   : void
//--------------------------------------------------------------
void gameplayMouseHandler(const MOUSE_EVENT_RECORD& mouseEvent)
{
    if (mouseEvent.dwEventFlags & MOUSE_MOVED) // update the mouse position if there are no events
    {
        g_mouseEvent.mousePosition = mouseEvent.dwMousePosition;
    }
    g_mouseEvent.buttonState = mouseEvent.dwButtonState;
    g_mouseEvent.eventFlags = mouseEvent.dwEventFlags;
}

//--------------------------------------------------------------
// Purpose  : Update function
//            This is the update function
//            double dt - This is the amount of time in seconds since the previous call was made
//
//            Game logic should be done here.
//            Such as collision checks, determining the position of your game characters, status updates, etc
//            If there are any calls to write to the console here, then you are doing it wrong.
//
//            If your game has multiple states, you should determine the current state, and call the relevant function here.
//
// Input    : dt = deltatime
// Output   : void
//--------------------------------------------------------------
void update(double dt)
{
    // get the delta time
    g_dElapsedTime += dt;
    g_dDeltaTime = dt;

    switch (g_eGameState)
    {
        case S_SPLASHSCREEN : splashScreenWait(); // game logic for the splash screen
            break;
        case S_GAME: updateGame(); // gameplay logic when we are in the game
            break;
    }
}


void splashScreenWait()    // waits for time to pass in splash screen
{
    if (g_dElapsedTime > 3.0) // wait for 3 seconds to switch to game mode, else do nothing
        g_eGameState = S_GAME;
}

void updateGame()       // gameplay logic
{
    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
                        // sound can be played here too.
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyReleased && g_sChar.m_cLocation.Y > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyReleased && g_sChar.m_cLocation.X > 0)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;
    }
    if (g_skKeyEvent[K_DOWN].keyReleased && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyReleased && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        g_sChar.m_bActive = !g_sChar.m_bActive;        
    }

   
}
void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
        g_bQuitGame = true;    
}

//--------------------------------------------------------------
// Purpose  : Render function is to update the console screen
//            At this point, you should know exactly what to draw onto the screen.
//            Just draw it!
//            To get an idea of the values for colours, look at console.h and the URL listed there
// Input    : void
// Output   : void
//--------------------------------------------------------------
void render()
{
    clearScreen();      // clears the current screen and draw from scratch 
    switch (g_eGameState)
    {
    case S_SPLASHSCREEN: renderSplashScreen();
        break;
    case S_GAME: renderGame();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    renderInputEvents();    // renders status of input events
    renderToScreen();       // dump the contents of the buffer to the screen, one frame worth of game
}

void clearScreen()
{
    // Clears the buffer with this colour attribute
    g_Console.clearBuffer(0x1F);
}

void renderToScreen()
{
    // Writes the buffer to the console, hence you will see what you have written
    g_Console.flushBufferToConsole();
}

void renderSplashScreen()  // renders the splash screen
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "A game in 3 seconds", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to change character colour", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);
}

void renderGame()
{
    renderMap();// renders the map to the buffer first
    CheckAndUpdate();
    renderCharacter();  // renders the character into the buffer
}

void renderMap()
{
    // Set up sample colours, and output shadings
    const char colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x0F,0xF7, 0xFF,0x7C,0xA2,0xAA,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6,0xC0,
    };
    // 0x1C No colour
    // 0x2C Green
    // 0x3C Light Blue
    // 0x4C Red
    // 0x5C Purple
    // 0x6C Yellow
    // 0x7C Gray
    // 0x8C Reddish Pink with gray border
    // 0x9C Reddish Pink with blue border
    // 0x1D No colour
    // 0x2D Green
    // 0x3D Light Blue
    // 0xFF White

    COORD c;
    // Black colour
    for (int i = 0; i < 17; i++)
    {
        c.X = i;
        c.Y = 4;
        g_Console.writeToBuffer(c, " ", colors[5]);
        c.X = i;
        c.Y = 10;
        g_Console.writeToBuffer(c, " ", colors[5]);
        c.X = i;
        c.Y = 14;
        g_Console.writeToBuffer(c, " ", colors[5]);
        c.X = i;
        c.Y = 20;
        g_Console.writeToBuffer(c, " ", colors[5]);


    }
    for (int i = 0; i < 5; i++)
    {
        c.X = 15;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 29;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 50;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 64;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
    }
    for (int i = 20; i < 25; i++)
    {
        c.X = 15;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 29;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 50;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 64;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
    }
    for (int i = 10; i < 15; i++)
    {
        c.X = 15;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 29;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 50;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = 64;
        c.Y = i;
        g_Console.writeToBuffer(c, "  ", colors[5]);



    }
    for (int i = 29; i < 51; i++)
    {
        c.X = i;
        c.Y = 4;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 10;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 14;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 20;
        g_Console.writeToBuffer(c, "  ", colors[5]);
    }
    for (int i = 64; i < 79; i++) {
        c.X = i;
        c.Y = 4;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 10;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 14;
        g_Console.writeToBuffer(c, "  ", colors[5]);
        c.X = i;
        c.Y = 20;
        g_Console.writeToBuffer(c, "  ", colors[5]);
    }
    // Gray colour oF ROAD
    for (int i = 17; i < 28; i++)
    {
        c.X = i;
        g_Console.writeToBuffer(c, "  ", colors[8]);
        for (int i = 0; i < 25; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[8]);
        }
    }
    for (int i = 52; i < 63; i++)
    {
        c.X = i;
        g_Console.writeToBuffer(c, "  ", colors[8]);
        for (int i = 0; i < 25; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[8]);
        }
    }
    for (int i = 0; i < 79; i++)
    {
        c.X = i;
        g_Console.writeToBuffer(c, "  ", colors[8]);
        for (int i = 5; i < 10; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[8]);
        }
    }
    for (int i = 0; i < 79; i++)
    {
        c.X = i;
        g_Console.writeToBuffer(c, "  ", colors[8]);
        for (int i = 15; i < 20; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[8]);
        }
    }
    // White colour of road
    for (int i = 0; i < 25; i++)
    {
        if (i == 1 || i == 2 || i == 3 || i == 6 || i == 7 || i == 8 || i == 11 || i == 12 || i == 13 || i == 16 || i == 17 || i == 18 || i == 21 || i == 22 || i == 23)
        {
            c.X = 22;
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[7]);
            c.X = 57;
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[7]);
        }
    }


    for (int i = 0; i < 79; i++)
    {
        if (i == 0 || i == 1 || i == 2 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12 || i == 13 || i == 31 || i == 32 || i == 33 || i == 34 || i == 35 || i == 36 || i == 43 || i == 44 || i == 45 || i == 46 || i == 47 || i == 48 || i == 66 || i == 67 || i == 68 || i == 69 || i == 70 || i == 71 || i == 77 || i == 78)
        {
            c.X = i;
            c.Y = 7;
            g_Console.writeToBuffer(c, "  ", colors[7]);
            c.X = i;
            c.Y = 17;
            g_Console.writeToBuffer(c, "  ", colors[7]);
        }
    }
    // Green Colour
    for (int i = 0; i < 14; i++)
    {
        c.X = i;
        for (int i = 21; i < 25; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        for (int i = 11; i < 14; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
        for (int i = 0; i < 4; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
    }
    for (int i = 31; i < 49; i++)
    {
        c.X = i;
        for (int i = 21; i < 25; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        for (int i = 11; i < 14; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
        for (int i = 0; i < 4; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
    }
    for (int i = 66; i < 79; i++)
    {
        c.X = i;
        for (int i = 21; i < 25; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        for (int i = 11; i < 14; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
        for (int i = 0; i < 4; i++)
        {
            c.Y = i;
            g_Console.writeToBuffer(c, "  ", colors[10]);
        }
        g_Console.writeToBuffer(c, "  ", colors[10]);
    }
}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0xC3;
    if (g_sChar.m_bActive)
    {
        charColor = 0xA1;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)1, charColor);
}

void renderFramerate()
{
    COORD c;
    // displays the framerate
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / g_dDeltaTime << "fps";
    c.X = g_Console.getConsoleSize().X - 9;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str());

    // displays the elapsed time
    ss.str("");
    ss << g_dElapsedTime << "secs";
    c.X = 0;
    c.Y = 0;
    g_Console.writeToBuffer(c, ss.str(), 0x59);
}

// this is an example of how you would use the input events
void renderInputEvents()
{
    // keyboard events
    COORD startPos = {50, 2};
    std::ostringstream ss;
    std::string key;
    for (int i = 0; i < K_COUNT; ++i)
    {
        ss.str("");
        switch (i)
        {
        case K_UP: key = "UP";
            break;
        case K_DOWN: key = "DOWN";
            break;
        case K_LEFT: key = "LEFT";
            break;
        case K_RIGHT: key = "RIGHT";
            break;
        case K_SPACE: key = "SPACE";
            break;
        default: continue;
        }
        if (g_skKeyEvent[i].keyDown)
            ss << key << " pressed";
        else if (g_skKeyEvent[i].keyReleased)
            ss << key << " released";
        else
            ss << key << " not pressed";

        COORD c = { startPos.X, startPos.Y + i };
        g_Console.writeToBuffer(c, ss.str(), 0x17);
    }

    // mouse events    
    ss.str("");
    ss << "Mouse position (" << g_mouseEvent.mousePosition.X << ", " << g_mouseEvent.mousePosition.Y << ")";
    g_Console.writeToBuffer(g_mouseEvent.mousePosition, ss.str(), 0x59);
    ss.str("");
    switch (g_mouseEvent.eventFlags)
    {
    case 0:
        if (g_mouseEvent.buttonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {

            ss.str("Left Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 1, ss.str(), 0x59);
            MakesBullet();
        }
        else if (g_mouseEvent.buttonState == RIGHTMOST_BUTTON_PRESSED)
        {
            ss.str("Right Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 2, ss.str(), 0x59);
        }
        else
        {
            ss.str("Some Button Pressed");
            g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 3, ss.str(), 0x59);
        }
        break;
    case DOUBLE_CLICK:
        ss.str("Double Clicked");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 4, ss.str(), 0x59);
        break;        
    case MOUSE_WHEELED:
        if (g_mouseEvent.buttonState & 0xFF000000)
            ss.str("Mouse wheeled down");
        else
            ss.str("Mouse wheeled up");
        g_Console.writeToBuffer(g_mouseEvent.mousePosition.X, g_mouseEvent.mousePosition.Y + 5, ss.str(), 0x59);
        break;
    default:        
        break;
    }
    
}



