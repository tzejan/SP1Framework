// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <time.h>

using namespace std;

double  g_dElapsedTime;
double  g_dDeltaTime;
SKeyEvent g_skKeyEvent[K_COUNT];
SMouseEvent g_mouseEvent;

// Game specific variables here
SGameChar   g_sChar;
SGameChar   Enemy[8];
SGameChar   Enemy2[8];
SGameChar   Enemy3[8];
SGameChar   Rock[8];
SGameChar   srock[8], srock2[8];
SGameChar   BulletTest;
SGameChar   Multishot[2];
SGameChar   BulletEnemy[8];
SGameChar   BulletEnemy2[8];
SGameChar   BulletEnemy3[8];
SGameChar   PowerUp;
SGameChar   Shield[8];
SGameChar   Boss;
SGameChar   BossBullet[3];

double timeToMove = 5;
double timeToMove2 = 5;
double timeToMove3 = 5;
double timeToMove4 = 5;
double timeToMove5 = 5;
double timeToMove6 = 5;
double BulletToMove = 5;
double BulletToMove2 = 5;
double BulletToMove3 = 5;
int  ekilled = 0;
int  score = 0;
int  number = rand() % 37 - 2;
bool PowerEaten = false;
bool shoot = false;

bool play = PlaySound(TEXT("audioWater.wav"), NULL, SND_LOOP | SND_ASYNC);
bool sSound = false;
int  sCount = 0;

int  kSound = 0;

int Special;
string SpecialText;

int difficulty = 2; //value = number of enemies to spawn
double start_gameTime = 0;  //Elapsed Time when starting
int life = 10;

//Boss Variables
int bosshealth = 30;
bool moveRight;
bool bossCanMove = false;
double bossTime = 60;
double bossTimeMove = 60;
double bossBulletTime = 60;

//Bullet Spawn Points
COORD bulletPoints[3];

EGAMESTATES g_eGameState = S_SPLASHSCREEN; // initial state

// Console object
Console g_Console(40, 30, "Space Wars");

#pragma region Startup

//--------------------------------------------------------------
// Purpose  : Initialisation function
//            Initialize variables, allocate memory, load data from file, etc. 
//            This is called once before entering into your main loop
// Input    : void
// Output   : void
//--------------------------------------------------------------
void init( void )
{
    sSound = false;
    life = 3;
    start_gameTime = 0;
    difficulty = 2;
    timeToMove = 5;
    timeToMove3 = 5;
    timeToMove4 = 5;
    timeToMove5 = 5;
    timeToMove6 = 5;
    BulletToMove = 5;
    BulletToMove2 = 5;
    BulletToMove3 = 5;
    play;

    bosshealth = 30;
    bossCanMove = false;
    bossTime = start_gameTime + 60;
    bossTimeMove = 60;
    bossBulletTime = 60;
    srand((unsigned)time(0));

    // Set precision for floating point output
    g_dElapsedTime = 0.0;    

    // sets the initial state for the game
    g_eGameState = S_SPLASHSCREEN;

    #pragma region BossInit
    //Boss
    Boss.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    Boss.m_cLocation.Y = g_Console.getConsoleSize().Y - 40;
    Boss.m_bActive = true;

    //Bullet Spawn Points
    BossBullet[0].m_cLocation.X = Boss.m_cLocation.X - 2;   //Left
    BossBullet[0].m_cLocation.Y = Boss.m_cLocation.Y + 4;
    BossBullet[0].m_bActive = false;

    BossBullet[1].m_cLocation.X = Boss.m_cLocation.X + 5;   //Center
    BossBullet[1].m_cLocation.Y = Boss.m_cLocation.Y + 4;
    BossBullet[1].m_bActive = false;

    BossBullet[2].m_cLocation.X = Boss.m_cLocation.X + 13;  //Right
    BossBullet[2].m_cLocation.Y = Boss.m_cLocation.Y + 4;
    BossBullet[2].m_bActive = false;

    for (int i = 0; i < 3; i++)
    {
        BossBullet[i].m_bActive = true;
    }
#pragma endregion
    #pragma region EnemyInit
    //Randomize starting spawn points
    for (int i = 0; i < (sizeof(Enemy) / sizeof(Enemy[0])); i++)
    {
        int number = rand() % (35 - 5) - 5; //from 4 - 34
        Enemy[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        Enemy[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;

        if (Enemy[i].m_cLocation.X == Enemy2[i].m_cLocation.X)
        {
            Enemy[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        }

        if (Enemy[i].m_cLocation.X)

            if (i < difficulty)
            {
                Enemy[i].m_bActive = true;  //Spawns [number] enemy first
            }
            else
            {
                Enemy[i].m_bActive = false; //Hides the rest
            }
    }
    for (int i = 0; i < (sizeof(Enemy2) / sizeof(Enemy2[0])); i++)
    {
        int number = rand() % 36 - 2;
        Enemy2[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        Enemy2[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;

        if (Enemy2[i].m_cLocation.X == Enemy[i].m_cLocation.X)
        {
            Enemy[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        }

        if (i < difficulty)
        {
            Enemy2[i].m_bActive = true;  //Spawns [number] enemy first
        }
        else
        {
            Enemy2[i].m_bActive = false; //Hides the rest
        }
        BulletEnemy[i].m_cLocation.X = Enemy2[i].m_cLocation.X;
        BulletEnemy[i].m_cLocation.Y = Enemy2[i].m_cLocation.Y - 1;
        BulletEnemy[i].m_bActive = true;



    }
    for (int i = 0; i < (sizeof(Enemy3) / sizeof(Enemy3[0])); i++)
    {
        int number = rand() % 36 - 2;
        Enemy3[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        Enemy3[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;

        if (i < difficulty)
        {
            Enemy3[i].m_bActive = true;  //Spawns [number] enemy first
        }
        else
        {
            Enemy3[i].m_bActive = false; //Hides the rest
        }


    }
    for (int i = 0; i < (sizeof(Rock) / sizeof(Rock[0])); i++)
    {
        int number = rand() % 36 - 2;
        Rock[i].m_cLocation.X = g_Console.getConsoleSize().X - number;
        Rock[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;

        if (i < difficulty)
        {
            Rock[i].m_bActive = true;  //Spawns [number] enemy first
        }
        else
        {
            Rock[i].m_bActive = false; //Hides the rest
        }

    }
    for (int i = 0; i < (sizeof(srock) / sizeof(srock[0])); i++)
    {

        srock[i].m_cLocation.X = Rock[i].m_cLocation.X - 1;
        srock[i].m_cLocation.Y = Rock[i].m_cLocation.Y;

        if (i < difficulty)
        {
            srock[i].m_bActive = true;  //Spawns [number] enemy first
        }
        else
        {
            srock[i].m_bActive = false; //Hides the rest
        }

    }
    for (int i = 0; i < (sizeof(srock2) / sizeof(srock2[0])); i++)
    {

        srock2[i].m_cLocation.X = Rock[i].m_cLocation.X;
        srock2[i].m_cLocation.Y = Rock[i].m_cLocation.Y - 1;

        if (i < difficulty)
        {
            srock2[i].m_bActive = true;  //Spawns [number] enemy first
        }
        else
        {
            srock2[i].m_bActive = false; //Hides the rest
        }

    }
#pragma endregion
    #pragma region PlayerStuffInit
    g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
    g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
    g_sChar.m_bActive = true;

    BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
    BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
    BulletTest.m_bActive = false;

    PowerUp.m_bActive = false;

#pragma endregion

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

#pragma endregion

#pragma region Handlers

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
    case S_GameOver: gameplayKBHandler(keyboardEvent);
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
#pragma endregion

#pragma region Update Functions

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
        start_gameTime = g_dElapsedTime;
}

void updateGame()       // gameplay logic
{
    if (start_gameTime != 0) 
    {
        if (g_dElapsedTime >= start_gameTime + 6.0 && g_dElapsedTime < start_gameTime + 20.0)
        {
            difficulty = 3;
        }
        else if (g_dElapsedTime >= start_gameTime + 20 && g_dElapsedTime < start_gameTime + 45)
        {
            difficulty = 5;
        }
        else if (g_dElapsedTime >= start_gameTime + 45)
        {
            difficulty = 8;
        }
    }

    if (g_dElapsedTime >= bossTime)
    {
        bossCanMove = true;
        bossTime = g_dElapsedTime + 60;
    }

    //Gonna clean this later on if got time
    bulletPoints[0].X = Boss.m_cLocation.X - 2;
    bulletPoints[0].Y = Boss.m_cLocation.Y + 4;

    bulletPoints[1].X = Boss.m_cLocation.X + 5;
    bulletPoints[1].Y = Boss.m_cLocation.Y + 4;

    bulletPoints[2].X = Boss.m_cLocation.X + 13;
    bulletPoints[2].Y = Boss.m_cLocation.Y + 4;

    processUserInput(); // checks if you should change states or do something else with the game, e.g. pause, exit
    moveCharacter();    // moves the character, collision detection, physics, etc
    checkCollision();
    moveEnemy();
    checkCollision();
    BulletMove();
    checkCollision();
    checkKilled();  

    movePowerUp();
    mMultishot();
    cMultishot();
    cShield();
    cHealth();
    cBomb();
    renderGameOver();
    moveEnemy2();
    moveEnemy3();
    EnemyBMove();
    EnemyBMove2();
    EnemyBMove3();
    RockMove();

    if (bossCanMove == true)
    {
        moveBoss();
        bossBulletMove();
    }
    else if (bosshealth <= 0) 
    {
        //Reset Boss Bullets
        for (int i = 0; i < sizeof(BossBullet) / sizeof(BossBullet[0]); i++)
        {
            BossBullet[i].m_bActive = false; // rendering
            BossBullet[i].m_cLocation = bulletPoints[i]; // resets the position to front of space ship
            BossBullet[i].m_bActive = true; // stops rendering
        }
    }

                        // sound can be played here too.
}

void moveCharacter()
{    
    // Updating the location of the character based on the key release
    // providing a beep sound whenver we shift the character
    if (g_skKeyEvent[K_UP].keyDown && g_sChar.m_cLocation.Y > 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y--;       
    }
    if (g_skKeyEvent[K_LEFT].keyDown && g_sChar.m_cLocation.X > 1)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X--;        
    }
    if (g_skKeyEvent[K_DOWN].keyDown && g_sChar.m_cLocation.Y < g_Console.getConsoleSize().Y - 2)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.Y++;        
    }
    if (g_skKeyEvent[K_RIGHT].keyDown && g_sChar.m_cLocation.X < g_Console.getConsoleSize().X - 2)
    {
        //Beep(1440, 30);
        g_sChar.m_cLocation.X++;        
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        BulletTest.m_bActive = true;
        Multishot[0].m_bActive = true;
        Multishot[1].m_bActive = true;
        shoot = true;
    }
    if (g_skKeyEvent[K_SPACE].keyDown)
    {
        sSound = true;
    }

   
}

void moveEnemy()
{
    if (g_dElapsedTime >= timeToMove) 
    {
        timeToMove = g_dElapsedTime + 0.4;

        for (int i = 0; i < difficulty; i++) 
        {
            Enemy[i].m_cLocation.Y++;  
        }
    }
}
void moveEnemy2()
{
    if (g_dElapsedTime >= timeToMove3)
    {
        timeToMove3 = g_dElapsedTime + 0.5;

        for (int i = 0; i < difficulty; i++)
        {
            Enemy2[i].m_cLocation.Y++;
            BulletEnemy[i].m_bActive = true;
        }

    }
}
void moveEnemy3()
{
    if (g_dElapsedTime >= timeToMove6)
    {
        timeToMove6 = g_dElapsedTime + 0.5;

        for (int i = 0; i < difficulty; i++)
        {
            Enemy3[i].m_cLocation.Y++;
            BulletEnemy2[i].m_bActive = true;
            BulletEnemy3[i].m_bActive = true;
        }

    }
}
void moveBoss()
{
    //Boss Patrol Route
    if (Boss.m_cLocation.X < 6)
    {
        moveRight = true;
    }
    else if (Boss.m_cLocation.X > 22)
    {
        moveRight = false;
    }

    if (g_dElapsedTime >= bossTimeMove)
    {
        bossTimeMove = g_dElapsedTime + 0.2;
        //Move Boss(Probably Relocate or make this function for all enemies)
        if (Boss.m_cLocation.Y > 5)
        {
            if (moveRight == true)
            {
                Boss.m_cLocation.X++;
            }
            else
            {
                Boss.m_cLocation.X--;
            }
        }
        else
        {
            Boss.m_cLocation.Y++;
        }
    }
}

void processUserInput()
{
    // quits the game if player hits the escape key
    if (g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }
    
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
    case S_GameOver: gameoverScene();
        break;
    }
    renderFramerate();      // renders debug information, frame rate, elapsed time, etc
    //renderInputEvents();    // renders status of input events
    renderGameInfo();
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
    renderMap();        // renders the map to the buffer first
    renderCharacter();  // renders the character into the buffer
    renderEnemy();  //renders the enemy (prototype)
    renderBullet(); //render spaceship bullet
    RbulletEnemy();
    RbulletEnemy2();
    RbulletEnemy3();
    renderEnemy2();
    renderEnemy3();
    renderRock();
    Srock();
    rMultishot();
    rShield();
    renderSpecial();

    if (bossCanMove == true)
    {
        renderBoss();
        renderBossBullet();
    }
}

void renderMap()
{
    //Set up sample colours, and output shadings
    const WORD colors[] = 
    {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

    COORD c;
    //for (int row = 0; row < 40; ++row)
    //{
    //    for (int col = 0; col < 30; ++col) 
    //    {
    //        if (col == 0 || col == 29) 
    //        {
    //            c.X = row;
    //            c.Y = col;
    //            colour(colors[1]);
    //        }
    //        else if (row == 0 || row == 39) 
    //        {
    //            c.X = row;
    //            c.Y = col;
    //            colour(colors[1]);
    //        }

    //        g_Console.writeToBuffer(c, " ", colors[3]); //wat the shit is this
    //    }

    //}

    ifstream file_("Map.txt");
    string line_;
    int rows = 0;
    
    while (getline(file_, line_))
    {
        for (int columns = 0; columns < line_.size(); columns++)
        {
            if (line_[columns] == '1')
            {
                c.X = rows;
                c.Y = columns;
                g_Console.writeToBuffer(c, " ", colors[0]);
            }
            else if (line_[columns] == '0')
            {
                c.X = rows;
                c.Y = columns;
                g_Console.writeToBuffer(c, " ", colors[4]);
            }
        }
        rows++;
    }
    
    //Laser Sight
    int playerSight = g_Console.getConsoleSize().Y + (g_sChar.m_cLocation.Y - 1); //distance from (player.x - 1) to top screen
    for (int i = 0; i < (playerSight - 29); i++)
    {
        COORD thisPos;
        thisPos.X = g_sChar.m_cLocation.X;
        thisPos.Y = g_sChar.m_cLocation.Y - i;
        g_Console.writeToBuffer(thisPos, " ", colors[3]);
    }

}

void renderCharacter()
{
    // Draw the location of the character
    WORD charColor = 0x0C;
    if (g_sChar.m_bActive)
    {
        charColor = 0x0A;
    }
    g_Console.writeToBuffer(g_sChar.m_cLocation, (char)3, charColor);
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

void renderEnemy()
{
    for (int i = 0; i < difficulty; i++) 
    {
        g_Console.writeToBuffer(Enemy[i].m_cLocation, (char)10);
    }

}
void renderEnemy2()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            g_Console.writeToBuffer(Enemy2[i].m_cLocation, (char)20);
        }

    }
}
void renderEnemy3()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            g_Console.writeToBuffer(Enemy3[i].m_cLocation, (char)20);
        }

    }
}
void renderRock()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty < 5)
        {
            WORD charColor = 0x0C;
            if (Rock[i].m_bActive) {
                charColor = 0xF6;
            }
            g_Console.writeToBuffer(Rock[i].m_cLocation, (char)30, charColor);

        }
    }
}
void Srock()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty < 5)
        {
            g_Console.writeToBuffer(srock[i].m_cLocation, (char)30);

        }
        if (difficulty < 5)
        {
            g_Console.writeToBuffer(srock2[i].m_cLocation, (char)30);

        }
    }

}
void renderBoss()
{
    string bossSprite[4] =
    { "    (00000000)     ",
     "  (0000UUUUUU0000)  ",
     "(00(  )0(UU)0(  )00)",
     " (U)   (0UU0)   (U) " };

    COORD bossPivot;
    bossPivot.X = Boss.m_cLocation.X - 4;
    bossPivot.Y = Boss.m_cLocation.Y;

    if (bosshealth > 0)
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < bossSprite[row].size(); col++)
            {
                g_Console.writeToBuffer(bossPivot, (bossSprite[row])[col]);
                bossPivot.X++;

                //Player Bullet Collision Detection
                if (BulletTest.m_bActive == true)
                {
                    if (BulletTest.m_cLocation.X == bossPivot.X && BulletTest.m_cLocation.Y == bossPivot.Y)
                    {
                        //Damage Boss
                        bosshealth--;

                        //Bullet Player Collision Reset
                        BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                        BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                        BulletTest.m_bActive = false; // stops rendering
                    }
                }

                //Multi Shot Power Collision Detection
                if (PowerEaten == true && PowerUp.m_bActive == false && Special == 1)
                {
                    for (int i = 0; i < 2; i++)
                    {
                        if (Multishot[i].m_bActive == true)
                        {
                            if ((Multishot[i].m_cLocation.X == bossPivot.X
                                && Multishot[i].m_cLocation.Y == bossPivot.Y))
                            {
                                bosshealth -= 1;

                                if (i == 0)
                                {
                                    Multishot[i].m_cLocation.X = BulletTest.m_cLocation.X - 2;
                                    Multishot[i].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;
                                }
                                else if (i == 1)
                                {
                                    Multishot[i].m_cLocation.X = BulletTest.m_cLocation.X + 2;
                                    Multishot[i].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;
                                }

                                Multishot[i].m_bActive = false;
                            }

                        }
                    }
                }
            }

            bossPivot.X = Boss.m_cLocation.X - 4;
            bossPivot.Y++;
        }
    }
    else
    {
        //Reset Boss Bullets
        for (int i = 0; i < sizeof(BossBullet)/sizeof(BossBullet[0]); i++) 
        {
            BossBullet[i].m_bActive = false; // rendering
            BossBullet[i].m_cLocation = bulletPoints[i]; // resets the position to front of space ship
            BossBullet[i].m_bActive = true; // stops rendering
        }

        //Reset Boss
        Boss.m_bActive = false;
        Boss.m_cLocation.X = g_Console.getConsoleSize().X / 2;
        Boss.m_cLocation.Y = g_Console.getConsoleSize().Y - 40;
        ekilled++;
        score += 10;
        bosshealth = 30;
        bossCanMove = false;
        Boss.m_bActive = true;
    }
}

void renderBullet()
{
    if (BulletTest.m_bActive == true)
    {
        if (sSound == true && sCount == 0)
        {
            Beep(500, 50);
            sCount = 1;
            sSound = false;
        }
        g_Console.writeToBuffer(BulletTest.m_cLocation, (char)6);
        BulletTest.m_cLocation.Y += 15 * g_dDeltaTime;
    }
    
}

void renderBossBullet()
{
    if (bosshealth > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (BossBullet[i].m_bActive == true)
            {
                g_Console.writeToBuffer(BossBullet[i].m_cLocation, (char)6);
                //BossBullet[i].m_cLocation.Y += 25 * g_dElapsedTime;
            }
        }
    }
}

void RbulletEnemy()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy[i].m_bActive == true)
            {
                g_Console.writeToBuffer(BulletEnemy[i].m_cLocation, (char)6);
                BulletEnemy[i].m_cLocation.Y += 25 * g_dDeltaTime;
            }
        }

    }

}
void RbulletEnemy2()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy2[i].m_bActive == true)
            {
                g_Console.writeToBuffer(BulletEnemy2[i].m_cLocation, (char)6);
                BulletEnemy2[i].m_cLocation.X += 25 * g_dDeltaTime;
            }
        }

    }
}
void RbulletEnemy3()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy3[i].m_bActive == true)
            {
                g_Console.writeToBuffer(BulletEnemy3[i].m_cLocation, (char)6);
                BulletEnemy3[i].m_cLocation.X += 25 * g_dDeltaTime;
            }
        }

    }
}
void EnemyBMove()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy[i].m_bActive == true)
            {
                if (g_dElapsedTime >= BulletToMove)
                {
                    BulletToMove = g_dElapsedTime + 0.1;

                    for (int i = 0; i < difficulty; i++)
                    {
                        if (difficulty >= 5)
                        {
                            BulletEnemy[i].m_cLocation.Y++;
                        }
                    }
                }
                if (BulletEnemy[i].m_cLocation.Y == 29)
                {

                    BulletEnemy[i].m_cLocation.X = Enemy2[i].m_cLocation.X;
                    BulletEnemy[i].m_cLocation.Y = Enemy2[i].m_cLocation.Y + 1; // resets the position to front of space ship
                    BulletEnemy[i].m_bActive = false; // stops renderin
                }
            }
            else
            {
                BulletEnemy[i].m_cLocation.X = Enemy2[i].m_cLocation.X;
                BulletEnemy[i].m_cLocation.Y = Enemy2[i].m_cLocation.Y + 1;
            }
        }
    }
}
void bossBulletMove()
{
    if (g_dElapsedTime >= bossBulletTime)
    {
        bossBulletTime = g_dElapsedTime + 0.1;
        if (bosshealth > 0)
        {
            //Normal Enemy Bullet Move
            for (int i = 0; i < 3; i++)
            {
                if (BossBullet[i].m_bActive == true)
                {
                    BossBullet[i].m_cLocation.Y++;

                    if (BossBullet[i].m_cLocation.Y >= 29) //Border Hit
                    {
                        BossBullet[i].m_bActive = false; // rendering
                        BossBullet[i].m_cLocation = bulletPoints[i]; // resets the position to front of space ship
                        BossBullet[i].m_bActive = true; // stops rendering
                    }
                }
                else
                {
                    BossBullet[i].m_cLocation = bulletPoints[i];
                }
            }
        }
    }

}

void EnemyBMove2()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy2[i].m_bActive == true)
            {
                if (g_dElapsedTime >= BulletToMove2)
                {
                    BulletToMove2 = g_dElapsedTime + 0.1;

                    for (int i = 0; i < difficulty; i++)
                    {
                        if (difficulty >= 5)
                        {
                            BulletEnemy2[i].m_cLocation.X++;
                        }
                    }
                }
                if (BulletEnemy2[i].m_cLocation.X == 39)
                {

                    BulletEnemy2[i].m_cLocation.X = Enemy3[i].m_cLocation.X + 1;
                    BulletEnemy2[i].m_cLocation.Y = Enemy3[i].m_cLocation.Y; // resets the position to front of space ship
                    BulletEnemy2[i].m_bActive = false; // stops renderin
                }
            }
            else
            {
                BulletEnemy2[i].m_cLocation.X = Enemy3[i].m_cLocation.X + 1;
                BulletEnemy2[i].m_cLocation.Y = Enemy3[i].m_cLocation.Y;
            }
        }
    }
}
void EnemyBMove3()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy3[i].m_bActive == true)
            {
                if (g_dElapsedTime >= BulletToMove3)
                {
                    BulletToMove3 = g_dElapsedTime + 0.1;

                    for (int i = 0; i < difficulty; i++)
                    {
                        if (difficulty >= 5)
                        {
                            BulletEnemy3[i].m_cLocation.X--;
                        }
                    }
                }
                if (BulletEnemy3[i].m_cLocation.X == 0)
                {

                    BulletEnemy3[i].m_cLocation.X = Enemy3[i].m_cLocation.X - 1;
                    BulletEnemy3[i].m_cLocation.Y = Enemy3[i].m_cLocation.Y; // resets the position to front of space ship
                    BulletEnemy3[i].m_bActive = false; // stops renderin
                }
            }
            else
            {
                BulletEnemy3[i].m_cLocation.X = Enemy3[i].m_cLocation.X - 1;
                BulletEnemy3[i].m_cLocation.Y = Enemy3[i].m_cLocation.Y;
            }
        }
    }
}
void BulletMove()
{
    if (BulletTest.m_bActive == true)
    {
        BulletTest.m_cLocation.Y = BulletTest.m_cLocation.Y - 1;
        if (BulletTest.m_cLocation.Y == 0)
        {

            BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
            BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
            BulletTest.m_bActive = false; // stops rendering
            sCount = 0;
        }

    }
    else
    {
        BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
        BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
    }
  
}
void RockMove()
{
    if (g_dElapsedTime >= timeToMove4)
    {
        timeToMove4 = g_dElapsedTime + 0.8;

        for (int i = 0; i < difficulty; i++)
        {
            Rock[i].m_cLocation.Y++;
            srock[i].m_cLocation.Y++;
            srock2[i].m_cLocation.Y++;

            if (srock[i].m_cLocation.Y == 29)
            {

                srock[i].m_cLocation.X = Rock[i].m_cLocation.X - 1;
                srock[i].m_cLocation.Y = Rock[i].m_cLocation.Y; // resets the position to front of space ship
                srock2[i].m_cLocation.X = Rock[i].m_cLocation.X;
                srock2[i].m_cLocation.Y = Rock[i].m_cLocation.Y - 1;
                srock[i].m_bActive = true; // stops renderin
            }
        }

    }
}
void checkCollision()
{
    if (BulletTest.m_bActive == true)
    {
        for (int i = 0; i < difficulty; i++)
        {
            if (BulletTest.m_cLocation.X == Enemy[i].m_cLocation.X && BulletTest.m_cLocation.Y == Enemy[i].m_cLocation.Y)
            {
                Enemy[i].m_bActive = false;
                Enemy[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % (35 - 5) - 5; //from 4 - 34
                Enemy[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Enemy[i].m_bActive = true;

                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering

                ekilled++;
                score++;
                sCount = 0;

                Beep(300, 50);
            }
            if (BulletTest.m_cLocation.X == Enemy2[i].m_cLocation.X && BulletTest.m_cLocation.Y == Enemy2[i].m_cLocation.Y)
            {
                Enemy2[i].m_bActive = false;
                Enemy2[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % (35 - 5) - 5;
                Enemy2[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Enemy2[i].m_bActive = true;

                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering

                ekilled++;
                score++;
                sCount = 0;
                Beep(300, 50);
            }
            if (BulletTest.m_cLocation.X == Enemy3[i].m_cLocation.X && BulletTest.m_cLocation.Y == Enemy3[i].m_cLocation.Y)
            {
                Enemy3[i].m_bActive = false;
                Enemy3[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                Enemy3[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Enemy3[i].m_bActive = true;

                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering

                ekilled++;
                score++;
            }
            if (BulletTest.m_cLocation.X == Rock[i].m_cLocation.X && BulletTest.m_cLocation.Y == Rock[i].m_cLocation.Y)
            {
                Rock[i].m_bActive = false;
                Rock[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                Rock[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Rock[i].m_bActive = true;


                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering


            }
            if (BulletTest.m_cLocation.X == srock[i].m_cLocation.X && BulletTest.m_cLocation.Y == srock[i].m_cLocation.Y)
            {
                srock[i].m_bActive = false;
                srock[i].m_cLocation.X = Rock[i].m_cLocation.X - 1;
                srock[i].m_cLocation.Y = Rock[i].m_cLocation.Y;
                srock[i].m_bActive = true;


                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering


            }
            if (BulletTest.m_cLocation.X == srock2[i].m_cLocation.X && BulletTest.m_cLocation.Y == srock2[i].m_cLocation.Y)
            {
                srock2[i].m_bActive = false;
                srock2[i].m_cLocation.X = Rock[i].m_cLocation.X;
                srock2[i].m_cLocation.Y = Rock[i].m_cLocation.Y - 1;
                srock2[i].m_bActive = true;

                BulletTest.m_cLocation.X = g_sChar.m_cLocation.X;
                BulletTest.m_cLocation.Y = g_sChar.m_cLocation.Y - 1; // resets the position to front of space ship
                BulletTest.m_bActive = false; // stops rendering


            }
        }

    }
    for (int i = 0; i < difficulty; i++)
    {
        if (difficulty >= 5)
        {
            if (BulletEnemy[i].m_bActive == true)
            {
                if (i < difficulty)
                {
                    if (BulletEnemy[i].m_cLocation.X == g_sChar.m_cLocation.X && BulletEnemy[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
                    {
                        life -= 1;
                        g_sChar.m_bActive = false;
                        g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
                        g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
                        g_sChar.m_bActive = true;
                    }
                }
            }
            if (BulletEnemy2[i].m_bActive == true)
            {
                if (i < difficulty)
                {
                    if (BulletEnemy2[i].m_cLocation.X == g_sChar.m_cLocation.X && BulletEnemy2[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
                    {
                        life -= 1;
                        g_sChar.m_bActive = false;
                        g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
                        g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
                        g_sChar.m_bActive = true;
                    }
                }
            }
            if (BulletEnemy3[i].m_bActive == true)
            {
                if (i < difficulty)
                {
                    if (BulletEnemy3[i].m_cLocation.X == g_sChar.m_cLocation.X && BulletEnemy3[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
                    {
                        life -= 1;
                        g_sChar.m_bActive = false;
                        g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
                        g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
                        g_sChar.m_bActive = true;
                    }
                }
            }
        }
    }
    for (int i = 0; i < difficulty; i++)
    {
        if (Enemy[i].m_cLocation.Y >= g_Console.getConsoleSize().Y - 1)
        {
            Enemy[i].m_bActive = false;
            Enemy[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % (35 - 5) - 5; //from 4 - 34
            Enemy[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
            Enemy[i].m_bActive = true;
        }
        for (int i = 0; i < difficulty; i++)
        {
            if (Enemy2[i].m_cLocation.Y >= g_Console.getConsoleSize().Y - 1)
            {
                Enemy2[i].m_bActive = false;
                Enemy2[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % (35 - 5) - 5; //from 4 - 34
                Enemy2[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Enemy2[i].m_bActive = true;
            }
        }
        for (int i = 0; i < difficulty; i++)
        {
            if (Enemy3[i].m_cLocation.Y >= g_Console.getConsoleSize().Y - 1)
            {
                Enemy3[i].m_bActive = false;
                Enemy3[i].m_cLocation.X = g_Console.getConsoleSize().X - rand() % (35 - 5) - 5; //from 4 - 34
                Enemy3[i].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                Enemy3[i].m_bActive = true;
            }
        }
    }
    for (int i = 0; i < sizeof(BossBullet) / sizeof(BossBullet[0]); i++)
    {
        if (BossBullet[i].m_cLocation.X == g_sChar.m_cLocation.X && BossBullet[i].m_cLocation.Y == g_sChar.m_cLocation.Y)
        {
            life--;
            g_sChar.m_bActive = false;
            g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
            g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
            g_sChar.m_bActive = true;
            BossBullet[i].m_bActive = false;
            BossBullet[i].m_cLocation = bulletPoints[i]; //reset to bullet spawn point
            BossBullet[i].m_bActive = true;
        }
    }   //Boss bullet collision check

}

void renderGameInfo()
{
    COORD info;
    info.X = g_Console.getConsoleSize().X;
    info.Y = g_Console.getConsoleSize().Y - 4;
    g_Console.writeToBuffer(info, "Score: " + to_string(score));

    info.X = g_Console.getConsoleSize().X - 15;
    info.Y = g_Console.getConsoleSize().Y - 1;
    g_Console.writeToBuffer(info, "Life: " + to_string(life));

    info.X = g_Console.getConsoleSize().X;
    info.Y = g_Console.getConsoleSize().Y - 2;
    g_Console.writeToBuffer(info, "Difficulty: " + to_string(difficulty));

    info.X = g_Console.getConsoleSize().X;
    info.Y = g_Console.getConsoleSize().Y - 3;
    g_Console.writeToBuffer(info, "Boss Health: " + to_string(bosshealth));

}
void gameoverScene()
{
    COORD c = g_Console.getConsoleSize();
    c.Y /= 3;
    c.X = c.X / 2 - 9;
    g_Console.writeToBuffer(c, "GAMEOVER", 0x03);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 20;
    g_Console.writeToBuffer(c, "Press <Space> to Play Again", 0x09);
    c.Y += 1;
    c.X = g_Console.getConsoleSize().X / 2 - 9;
    g_Console.writeToBuffer(c, "Press 'Esc' to quit", 0x09);

    if (g_skKeyEvent[K_SPACE].keyReleased)
    {
        init();
    }
    else if (g_skKeyEvent[K_ESCAPE].keyReleased)
    {
        g_bQuitGame = true;
    }
}

void renderGameOver()
{
    for (int i = 0; i < difficulty; i++)
    {
        if (g_sChar.m_cLocation.X == Enemy[i].m_cLocation.X && g_sChar.m_cLocation.Y == Enemy[i].m_cLocation.Y)
        {
            life -= 1;
            g_sChar.m_bActive = false;
            g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
            g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
            g_sChar.m_bActive = true;
            Beep(175, 70);
        }
        if (g_sChar.m_cLocation.X == Enemy2[i].m_cLocation.X && g_sChar.m_cLocation.Y == Enemy2[i].m_cLocation.Y)
        {
            if (Enemy2[i].m_bActive == true)
            {
                life -= 1;
                g_sChar.m_bActive = false;
                g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
                g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
                g_sChar.m_bActive = true;
            }
        }
        if (g_sChar.m_cLocation.X == Enemy3[i].m_cLocation.X && g_sChar.m_cLocation.Y == Enemy3[i].m_cLocation.Y)
        {
            if (Enemy3[i].m_bActive == true)
            {
                life -= 1;
                g_sChar.m_bActive = false;
                g_sChar.m_cLocation.X = g_Console.getConsoleSize().X / 2;
                g_sChar.m_cLocation.Y = g_Console.getConsoleSize().Y - 5;
                g_sChar.m_bActive = true;
            }
        }
        if (life <= 0)
        {
            g_eGameState = S_GameOver;
        }
    }
    

}

void rMultishot()
{
    for (int i = 0; i < 2; i++)
    {
        if (Multishot[i].m_bActive == true && PowerEaten == true && PowerUp.m_bActive == false && Special == 1)
        {
            g_Console.writeToBuffer(Multishot[i].m_cLocation, (char)6);
            Multishot[i].m_cLocation.Y += 25 * g_dDeltaTime;
        }
    }
}

void mMultishot()
{
    if (PowerEaten == true && PowerUp.m_bActive == false && Special == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (Multishot[i].m_bActive == true && shoot == true)
            {
                Multishot[i].m_cLocation.Y--;
                if (Multishot[i].m_cLocation.Y == 0)
                {
                    Multishot[i].m_bActive = false;
                    if (i == 0)
                    {
                        Multishot[i].m_cLocation.X = g_sChar.m_cLocation.X - 2;
                        Multishot[i].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
                    }
                    else if (i == 1)
                    {
                        Multishot[i].m_cLocation.X = g_sChar.m_cLocation.X - 2;
                        Multishot[i].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
                    }
                }

            }
            else
            {
                if (i == 0)
                {
                    Multishot[i].m_cLocation.X = g_sChar.m_cLocation.X - 2;
                    Multishot[i].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
                }
                else if (i == 1)
                {
                    Multishot[i].m_cLocation.X = g_sChar.m_cLocation.X + 2;
                    Multishot[i].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;
                }
            }

        }
    }
}

void cMultishot()
{
    if (PowerEaten == true && PowerUp.m_bActive == false && Special == 1)
    {
        for (int i = 0; i < 2; i++)
        {
            if (Multishot[i].m_bActive == true)
            {
                for (int e = 0; e < difficulty; e++)
                {
                    if ((Multishot[i].m_cLocation.X == Enemy[e].m_cLocation.X && Multishot[i].m_cLocation.Y == Enemy[e].m_cLocation.Y) || Multishot[i].m_cLocation.Y <= 0
                        || (Multishot[i].m_cLocation.X == Enemy2[e].m_cLocation.X && Multishot[i].m_cLocation.Y == Enemy2[e].m_cLocation.Y))
                    {
                        if (Multishot[i].m_cLocation.X == Enemy[e].m_cLocation.X && Multishot[i].m_cLocation.Y == Enemy[e].m_cLocation.Y)
                        {

                            Enemy[e].m_bActive = false;

                            Enemy[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                            Enemy[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                            Enemy[e].m_bActive = true;

                            ekilled++;
                            score++;
                            Beep(350, 50);
                        }

                        if (Multishot[i].m_cLocation.X == Enemy2[e].m_cLocation.X && Multishot[i].m_cLocation.Y == Enemy2[e].m_cLocation.Y)
                        {
                            Enemy2[e].m_bActive = false;

                            Enemy2[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                            Enemy2[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                            Enemy2[e].m_bActive = true;

                            ekilled++;
                            score++;
                            Beep(350, 50);
                        }

                        if (i == 0)
                        {
                            Multishot[i].m_cLocation.X = BulletTest.m_cLocation.X - 2;
                            Multishot[i].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;
                        }
                        else if (i == 1)
                        {
                            Multishot[i].m_cLocation.X = BulletTest.m_cLocation.X + 2;
                            Multishot[i].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;
                        }


                        Multishot[i].m_bActive = false;

                    }
                }

            }
        }
    }
    else
    {
        Multishot[0].m_cLocation.X = BulletTest.m_cLocation.X - 2;
        Multishot[0].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;

        Multishot[1].m_cLocation.X = BulletTest.m_cLocation.X + 2;
        Multishot[1].m_cLocation.Y = BulletTest.m_cLocation.Y - 1;

    }
}

void rShield()
{

    if (PowerEaten == true && PowerUp.m_bActive == false && Special == 4)
    {
        Shield[0].m_cLocation.X = g_sChar.m_cLocation.X - 1;
        Shield[0].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

        Shield[1].m_cLocation.X = g_sChar.m_cLocation.X;
        Shield[1].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

        Shield[2].m_cLocation.X = g_sChar.m_cLocation.X + 1;
        Shield[2].m_cLocation.Y = g_sChar.m_cLocation.Y - 1;

        Shield[3].m_cLocation.X = g_sChar.m_cLocation.X - 1;
        Shield[3].m_cLocation.Y = g_sChar.m_cLocation.Y;

        Shield[4].m_cLocation.X = g_sChar.m_cLocation.X + 1;
        Shield[4].m_cLocation.Y = g_sChar.m_cLocation.Y;

        Shield[5].m_cLocation.X = g_sChar.m_cLocation.X - 1;
        Shield[5].m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

        Shield[6].m_cLocation.X = g_sChar.m_cLocation.X;
        Shield[6].m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

        Shield[7].m_cLocation.X = g_sChar.m_cLocation.X + 1;
        Shield[7].m_cLocation.Y = g_sChar.m_cLocation.Y + 1;

        for (int i = 0; i < 8; i++)
        {
            g_Console.writeToBuffer(Shield[i].m_cLocation, 'X');
        }
    }

}

void cShield()
{
    if (PowerEaten == true && PowerUp.m_bActive == false && Special == 4)
    {
        for (int s = 0; s < 8; s++)
        {
            for (int e = 0; e < difficulty; e++)
            {

                if (Shield[s].m_cLocation.X == Enemy[e].m_cLocation.X && Shield[s].m_cLocation.Y == Enemy[e].m_cLocation.Y)
                {
                    Enemy[e].m_bActive = false;

                    Enemy[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                    Enemy[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                    Enemy[e].m_bActive = true;

                    ekilled++;
                    score++;
                    Beep(440, 70);
                }

                if (Shield[s].m_cLocation.X == Enemy2[e].m_cLocation.X && Shield[s].m_cLocation.Y == Enemy2[e].m_cLocation.Y)
                {
                    Enemy2[e].m_bActive = false;

                    Enemy2[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
                    Enemy2[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
                    Enemy2[e].m_bActive = true;

                    ekilled++;
                    score++;
                    Beep(440, 70);
                }

                if (Shield[s].m_cLocation.X == BulletEnemy[e].m_cLocation.X && Shield[s].m_cLocation.Y == BulletEnemy[e].m_cLocation.Y)
                {
                    BulletEnemy[e].m_bActive = false;

                    BulletEnemy[e].m_cLocation.X = Enemy2[e].m_cLocation.X;
                    BulletEnemy[e].m_cLocation.Y = Enemy2[e].m_cLocation.Y - 1;                    
                    BulletEnemy[e].m_bActive = true;

                    ekilled++;
                    Beep(530, 70);
                }
                
            }
            for (int i = 0; i < sizeof(BossBullet) / sizeof(BossBullet[0]); i++)
            {
                if (Shield[s].m_cLocation.X == BossBullet[i].m_cLocation.X
                    && Shield[s].m_cLocation.Y == BossBullet[i].m_cLocation.Y)
                {
                    BossBullet[i].m_bActive = false;
                    BossBullet[i].m_cLocation = bulletPoints[i]; // resets the position to front of space ship
                    BossBullet[i].m_bActive = true; // stops rendering

                    ekilled++;
                    Beep(440, 70);
                }
            }
        }

    }
}

void cHealth()
{
    if (PowerEaten == true && Special == 2)
    {
        life = 3;
        ekilled = 0;
        Beep(320, 30);
        Beep(400, 30);
        PowerEaten = false;
    }
}

void cBomb()
{
    if (PowerEaten == true && Special == 3)
    {
        for (int e = 0; e < difficulty; e++)
        {
            Enemy[e].m_bActive = false;
            Enemy2[e].m_bActive = false;
            BulletEnemy[e].m_bActive = false;

            Enemy[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
            Enemy2[e].m_cLocation.X = g_Console.getConsoleSize().X - rand() % 38 - 2;
            BulletEnemy[e].m_cLocation.X = Enemy2[e].m_cLocation.X;

            BulletEnemy[e].m_cLocation.Y = Enemy2[e].m_cLocation.Y - 1;
            Enemy[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
            Enemy2[e].m_cLocation.Y = g_Console.getConsoleSize().Y - 29;

            Enemy[e].m_bActive = true;
            Enemy2[e].m_bActive = true;
            BulletEnemy[e].m_bActive = true;
        }

        if (Boss.m_cLocation.Y < g_Console.getConsoleSize().Y - 40) 
        {
            bosshealth -= 5;
        }

        PowerEaten = false;
        ekilled = 0;
        Beep(200, 100);
    }
}

void movePowerUp()
{
    if (g_dElapsedTime >= timeToMove2)
    {
        timeToMove2 = g_dElapsedTime + 0.5;
        PowerUp.m_cLocation.Y++;

        if (PowerUp.m_bActive == true)
        {
            if (Special == 4)
            {
                Special = 1;
            }
            else
            {
                Special++;
            }
        }


    }

    if ((PowerUp.m_cLocation.Y == g_sChar.m_cLocation.Y && PowerUp.m_cLocation.X == g_sChar.m_cLocation.X) || PowerUp.m_cLocation.Y == 29)
    {
        if (PowerUp.m_cLocation.Y == 29)
        {
            SpecialText = "";
        }
        else
        {
            PowerEaten = true;
        }
        PowerUp.m_bActive = false;
    }
}

void renderSpecial()
{
    if (PowerUp.m_bActive == true)
    {
        if (Special == 1)
        {
            SpecialText = "Multishot";
            g_Console.writeToBuffer(PowerUp.m_cLocation, 'M');
        }
        else if (Special == 2)
        {
            SpecialText = "Health";
            g_Console.writeToBuffer(PowerUp.m_cLocation, 'H');
        }
        else if (Special == 3)
        {
            SpecialText = "Bomb";
            g_Console.writeToBuffer(PowerUp.m_cLocation, 'B');
        }
        else if (Special == 4)
        {
            SpecialText = "Shield";
            g_Console.writeToBuffer(PowerUp.m_cLocation, 'S');
        }

    }


}

void checkKilled()
{
    if ((ekilled % 10 == 0) && (ekilled > 0) && PowerUp.m_bActive == false)
    {
        number = rand() % (35 - 5) - 5;
        PowerUp.m_cLocation.X = (g_Console.getConsoleSize().X - number);
        for (int i = 0; i < difficulty; i++)
        {
            if ((PowerUp.m_cLocation.X == Enemy[i].m_cLocation.X) || (PowerUp.m_cLocation.X == Enemy2[i].m_cLocation.X))
            {
                number = rand() % (35 - 5) - 5;
                PowerUp.m_cLocation.X = (g_Console.getConsoleSize().X - number);
                while (PowerUp.m_cLocation.X > 39 || PowerUp.m_cLocation.Y < 1)
                {
                    PowerUp.m_cLocation.X = (g_Console.getConsoleSize().X - (rand() % (35 - 5) - 5));
                }
            }
        }

        PowerUp.m_cLocation.Y = g_Console.getConsoleSize().Y - 29;
        ekilled = 0;
        PowerUp.m_bActive = true;

    }
}
#pragma endregion



