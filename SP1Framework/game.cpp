// This is the main file for the game logic and function
//This is a test just ignore.
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

double refresh = 0;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;

map fruits[5]; //Columns

int score = 0;
int AppleCollection = 0;
int OrangeCollection = 0;
int GrapeCollection = 0;
int WormCollection = 0;

const WORD colors[] = 
{
	0x00, 0x04, 0x0C, 0x05, 0x08
};

int column;
int column2;
basket player;
int detect;
bool collision = false;
bool spawn = true;

void init()
{
	printMap();

	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"SP1 Framework");

	// Sets the console size, this is the biggest so far.
	setConsoleSize(79, 28);

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	// set the character to be in the center of the screen.
	charLocation.X = consoleSize.X / 2;
	charLocation.Y = consoleSize.Y / 2;

	player.location.X = 25;
	player.location.Y = 23;

	elapsedTime = 0.0;

	//Print everything as default (No fruits)

	for(int x = 0 ; x < 5 ; x++) //Columns
	{
		for(int y = 0 ; y < 9; y++) //Rows
		{
			fruits[x].fruitcheck[y] = false;
			fruits[x].character[y] = ' ';
			fruits[x].color[y] = 0;
		}
	}
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
	keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
	keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
}

void update(double dt)
{
	getcolumn();

	// get the delta time
	elapsedTime += dt;
	deltaTime = dt;
	refresh += dt;

	if(refresh > 1)
	{
		collision = false;
		gameplay();
		refresh = 0;
	}

	// Updating the location of the character based on the key press

	if (keyPressed[K_LEFT] && player.location.X > 19)
	{
		gotoXY(player.location.X, player.location.Y);
		cout << "   ";
		player.location.X -= 3;
		Beep(1440, 30);
	}

	if (keyPressed[K_RIGHT] && player.location.X < 31)
	{
		gotoXY(player.location.X, player.location.Y);
		cout << "   ";
		player.location.X += 3;
		Beep(1440, 30);
	}

	// quits the game if player hits the escape key
	if (keyPressed[K_ESCAPE])
		g_quitGame = true;

	//Detection

	gotoXY(26,25);
	colour(0x07);
	cout << detect;
	gotoXY(26,26);
	colour(0x07);
	cout << player.location.X;
	checkcollision();
}
void PatternAlgorithm1()
{
	srand(time(NULL));

	column = rand()%5;
	fruits[column].fruitcheck[0] = true;

	int identify = rand()%4;

	switch(identify)
	{
	case 0: fruits[column].character[0] = 'A'; //Apple
		fruits[column].color[0] = 1;
		break;

	case 1: fruits[column].character[0] = 'O'; //Orange
		fruits[column].color[0] = 2;
		break;

	case 2: fruits[column].character[0] = 'G'; //Grape
		fruits[column].color[0] = 3;
		break;

	case 3: fruits[column].character[0] = '~'; //Worm
		fruits[column].color[0] = 4;
		break;
	}
	spawn = false;
}
int RowSpace=0;
void PatternAlgorithm2()
{
	//WORM INVASION :D
	if(RowSpace%2==0)
	{
		for(int x=0;x<5;++x)
		{
			
				fruits[x].fruitcheck[0]=true;
				fruits[x].character[0]='~';
				fruits[x].color[0]=4;
		}
			int EscapePlan=rand()%3;
			
			fruits[EscapePlan].fruitcheck[0]=false;
		
		
		
	}
	else
	{
		for(int x=0;x<5;++x)
		{
				fruits[x].fruitcheck[0]=false;
		}
		
	}

	RowSpace+=1;

	if(WormCollection==1)
			{
				g_quitGame=true;
			}
}


int Shift=0;
void PatternAlgorithm3()
{
	//Swirl
	fruits[Shift].fruitcheck[0]=true;
	fruits[Shift].character[0]='O';
	fruits[Shift].color[0]=2;
	if(Shift<4)
	{
		Shift++;
	}

	else
	{
		Shift=0;
	}


}
void gameplay()
{
	//Clear current fruits location

	for(int x = 0; x < 17; x++) //Spacing for Rows
	{
		for(int y = 0; y < 13; y++) //Spacing for Columns
		{
			gotoXY(y + 20, x + 7);
			colour(colors[0]);
			cout << " ";
		}
	}

	//Pushing the character down one row

	for(int x = 4; x >= 0; x--)	//Columns
	{
		for(int y = 8; y > 0; y--)	//Rows
		{
			fruits[x].fruitcheck[y] = fruits[x].fruitcheck[y - 1];
			fruits[x].character[y] = fruits[x].character[y - 1];
			fruits[x].color[y] = fruits[x].color[y - 1];
		}
	}

	for(int x = 0; x < 5; x++) //Reset top row
	{
		fruits[x].fruitcheck[0] = false;
		fruits[x].character[0] = ' ';
		fruits[x].color[0] = 0;
	}

	//Spawning process

	if(spawn == true)
	{
		PatternAlgorithm2();
	}

	else if (spawn == false)
	{
		for(int x = 0; x < 5; x++) //Reset top row
		{
			fruits[x].fruitcheck[0] = false;
			fruits[x].character[0] = ' ';
			fruits[x].color[0] = 0;
		}

		spawn = true;
	}
}

void render()
{
	colour(0x0F);

	//Movement of basket

	gotoXY(player.location.X,player.location.Y);
	cout << "\\_/"<<endl;



	//Movement of fruits (Printing new location)

	for(int x = 0; x < 5; x++)	//Columns
	{
		for(int y = 0; y < 9; y++) //Rows
		{
			gotoXY(20 + (x * 3), 7 + (y * 2));

			if(fruits[x].fruitcheck[y] == true)
			{
				colour(colors[fruits[x].color[y]]);

				if (fruits[x].character[y] != '~')
				{
					cout << "O";
				}

				else
				{
					cout << fruits[x].character[y];
				}
				colour(colors[0]);
			}

			else
			{
				cout << " ";
			}

		}
	}

	colour(0x07);

	gotoXY(58, 0);
	cout << "Frames Per Second: " << 1.0 / deltaTime << endl;

	gotoXY(0, 0);
	cout << "Timer: " << elapsedTime << "secs" << endl;

	gotoXY(0, 3);
	cout << "Score: " << score << endl;

	gotoXY(0, 5);
	cout << "Apple: " << AppleCollection << endl;

	gotoXY(12, 5);
	cout << "Orange: " << OrangeCollection << endl;

	gotoXY(26, 5);
	cout << "Grape: " << GrapeCollection << endl;

	gotoXY(39, 5);
	cout << "Worm: " << WormCollection << endl;

	cout << endl;

}

void getcolumn()
{
	switch(player.location.X)
	{
	case 19: detect = 0;
		break;

	case 22: detect = 1;
		break;

	case 25: detect = 2;
		break;

	case 28: detect = 3;
		break;

	case 31: detect = 4;
		break;
	}
}

void checkcollision()
{
	if(collision == false && fruits[detect].fruitcheck[8] == true) //Basket detected
	{
		effects();
		collision = true;
	}
}

void startscreen()
{
	cout<<  "  ******    ***  ********  ******  ***  ***      ***   *** *** ***   *** ********   ***   \n"
		" ********  ***** ******** ******** ***  ***      ****  *** *** ****  *** ********  *****  \n"
		" ***  *** **   **  ****   ***  *** ***  ***      ***** *** *** ***** ***      *** **   ** \n" 
		" ***      **   **  ****   ***      ********      ***** *** *** ***** ***      *** **   ** \n"
		" ***      *******  ****   ***      ********      ********* *** ********* ***  *** ******* \n"
		" ***  *** *******  ****   ***  *** ***  ***      *** ***** *** *** ***** ***  *** ******* \n"
		" ******** **   **  ****   ******** ***  ***      ***  **** *** ***  **** ******** **   ** \n" 
		"   *****  **   **  ****    ******  ***  ***      ***   *** *** ***   ***  ******  **   ** " << endl;

	cout << endl;
	cout << "[1] START" << endl;
	cout << "[2] OPTIONS" << endl;
	cout << "[3] SCOREBOARD" << endl;
	cout << "[4] EXIT PROGRAM" << endl << endl;

	int input;

	for(int check = 0; check == 0;)
	{
		input = getch() - 48;
		state stage = GAME;
		while(stage != END)
		{
			if(input == 1)
			{
				system("cls");
GAME:play();
				system("pause");
			}

			else if (input == 2)
			{
				system("cls");
OPTIONS:options();
				system("pause");
			}

			else if (input == 3)
			{
				system("cls");
SCOREBOARD:scoreboard();
				system("pause");
			}

			else if (input == 4)
			{
				system("cls");
HOME:endscreen();
				system("pause");
			}

			else
			{
				cout << "Invalid input!" << endl;
				input = getch() - 48;
				check++;
			}
		}
	}
}

void endscreen()
{
	system("cls");
	colour(FOREGROUND_RED);

	cout << "********* **    **     **     ***    *** ***     ***   ****         \n"
		"********* **    **    ****    *****  *** ***    ***  ********         \n"
		"   ***    **    **   **  **   ****** *** ***   ***  ****  ****     \n"
		"   ***    ********  **    **  ********** ********    ****       \n"
		"   ***    ******** ********** ********** ********      *****         \n"
		"   ***    **    ** ***    *** *** ****** ***   ***  ***   ****        \n"
		"   ***    **    ** ***    *** ***  ***** ***    ***  *********		\n"
		"   ***    **    ** ***    *** ***    *** ***     ***   ****" << endl;

	cout << endl;

	cout <<	"    ****     ********* *********   ***       ***    *****     ***    ***	\n"
		"  ********   ********* *********    ***     ***   ***   ***   ***    ***	\n"
		" ****  ****  ***       ***           ***   ***   ***     ***  ***    ***	\n"		      
		"  ****       ***       ***            *** ***   ****     **** ***    ***	\n"
		"    ******   ********  ********        *****    ****     **** ***    ***	\n"
		"      *****  ***       ***             ****     ****     **** ***    ***	\n"
		" ****   **** ***       ***            ****       ***     ***  ****  ****	\n"
		"  *********  ********* *********     ****         ***   ***    ********	\n"
		"   ******    ********* *********    ****            *****       ******   " << endl;

	cout << endl;

	cout <<
		"      ***       *****       ***    ***  ***   ***  \n"
		"     ** **    *********    ** **   ***  ****  ***  \n"
		"    **   **  ***     ***  **   **  ***  ***** ***  \n"
		"   **     ** ***     *** **     ** ***  *********  \n"
		"   ********* ***         ********* ***  *********  \n"
		"   ********* ***    **** ********* ***  *********  \n"
		"   **     ** ***     *** **     ** ***  *** *****  \n"
		"   **     **  *********  **     ** ***  ***  ****  \n"
		"   **     **   *******   **     ** ***  ***   ***   " << endl << endl;

	exit(1);
}

void options()
{
	system("cls");
	colour(FOREGROUND_RED);

	cout << endl;
	cout << "Newbie... you think you have what it takes to be a CATCH NINJA huh?" << endl << endl;

	cout << "HOW TO PLAY: " << endl << endl;

	cout << "1) Catch the fruits with the basket!" << endl;
	cout << "2) Avoid the nasty worms!" << endl;
	cout << "3) Be the best Catch Ninja you can be!" << endl << endl;

	cout << "CREATORS: " << endl << endl;
	cout << "Giggs" << endl;
	cout << "Rayson" << endl;
	cout << "Ruoyun" << endl;
	cout << "Jessica" << endl << endl;

	exit(1);
}

void scoreboard()
{
	system("cls");
	colour(FOREGROUND_RED);

	cout << "****        **********  ********         *******         **********  *******        " <<
		endl << "****        **********  ********         ****  ****      **********  **** ****       " <<
		endl << "****        ****        ****  ****       ****    ****    ****        ****   ****      " <<
		endl << "****        ********    ***********      ****     ****   ********    ****  *****       " <<
		endl << "****        ********    ************     ****     *****  ********    *********          " <<
		endl << "****        ****        ****     ****    ****    *****   ****        **** ****           " <<
		endl << "**********  **********  ****      ****   ****  ******    **********  ****  ****           " <<
		endl << "**********  **********  ****       ****  **********      **********  ****   *****          " <<
		endl << endl <<
		endl << "                                ********       **********    ********         *******       *******         " <<
		endl << "                                **** *****    *****   ****   *********        **** ****     ****  ****       " <<
		endl << "                                ****  ****    ****     ****  ****  ****       ****   ****   ****    ****      " <<
		endl << "                                *********     ****     ****  ***********      ****  *****   ****     ****      " <<
		endl << "                                **** ****     ****     ****  ************     *********     ****    *****       " <<
		endl << "                                ****  *****   ****     ****  ****     ****    **** ****     ****    *****        " <<
		endl << "                                ****  ******  *****  *****   ****      ****   ****  ****    ****  ******          " <<
		endl << "                                ***********     *********    ****       ****  ****   *****  **********             " <<
		endl <<
		endl;

	exit(1);
}

void printMap()
{
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout <<
		"*******      *                          ,      ,,,,,,,,\n"
		"*******    **                            ,,    ,,,,,,,,\n"
		"*******   **                              ,,   ,,,,,,,,\n"
		"*******  **                                ,,  ,,,,,,,,\n"
		"**********                                  ,,,,,,,,,,,\n"
		"*********                                    ,,,,,,,,,,\n"
		"********                                      ,,,,,,,,,\n"
		"********                                       ,,,,,,,,\n"
		"********                                       ,,,,,,,,\n"
		"********                                       ,,,,,,,,\n"
		"********                                       ,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n"
		"*********                                     ,,,,,,,,,\n" << endl;
}

void effects()
{
	if(fruits[detect].character[8] == 'A')
	{
		AppleCollection += 1;
		score += 1;
	}

	else if(fruits[detect].character[8] == 'O')
	{
		OrangeCollection += 1;
		score += 3;
	}

	else if(fruits[detect].character[8] == 'G')
	{
		GrapeCollection += 1;
		score = score * 2;
	}

	else if(fruits[detect].character[8] == '~')
	{
		WormCollection += 1;
		score -= 5; 
	}

	if(score < 0)
	{
		score = 0;
	}
}