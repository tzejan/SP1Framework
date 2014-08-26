// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cstdio>
#include <vector>
#include <windows.h>

using std::stoi;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;
using std::ifstream;
using std::ofstream;

double refresh = 0;
double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
COORD charLocation;
COORD consoleSize;


map fruits[5]; //Columns
basket player;

int lives = 5;
int score = 0;
int AppleCollection = 0;
int OrangeCollection = 0;
int GrapeCollection = 0;
int WormCollection = 0;

int column;
int column2;
int detect;

bool collision = false;
bool spawn = true;

int RowSpace = 0;

const WORD colors[] = 
{
	0x00, 0x0C, 0x04, 0x05, 0x08
};

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
	player.location.Y = 24;

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

	if(refresh > 0.5)
	{
		collision = false; //Default collision is false
		gameplay();
		refresh = 0;  //Reset refresh
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
void PatternAlgorithm2()
{
	//WORM INVASION
	srand(time(0));
	if(RowSpace%2 == 0)
	{
		for(int x = 0; x < 5; ++x)
		{
			fruits[x].fruitcheck[0]=true;
			fruits[x].character[0]='~';
			fruits[x].color[0]=4;
		}
		int EscapePlan = rand()%4;

		fruits[EscapePlan].fruitcheck[0] = false;	
	}

	else
	{
		for(int x = 0;x < 5; ++x)
		{
			fruits[x].fruitcheck[0] = false;
		}

	}

	RowSpace += 1;

	if(WormCollection==1)
	{
		gameover();
	}
}
int Shift = 0;
void PatternAlgorithm3A()
{
	//Swirl
	fruits[Shift].fruitcheck[0] = true;
	fruits[Shift].character[0] = 'O';
	fruits[Shift].color[0] = 2;

	if(Shift < 4)
	{
		Shift++;
	}

	else
	{
		Shift = 0;
	}
}

void PatternAlgorithm3B()
{
	int y=4;
	fruits[y-Shift].fruitcheck[0] = true;
	fruits[y-Shift].character[0]='O';
	fruits[y-Shift].color[0] = 2;
	if(Shift<5)
	{
	++Shift;
	}
	else
	{
		Shift=0;
	}
}

void PatternAlgorithm3()
{
	if(OrangeCollection%11<6)
	{
		PatternAlgorithm3A();

	}
	else
	{
		PatternAlgorithm3B();

	}
}



void PatternAlgorith4()
{

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
		PatternAlgorithm3();
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
	cout << "\\_/";

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

	gotoXY(30,1);
	cout << "Lives left: " << lives << endl;

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

	if (lives == 0)
	{
		gameover();
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
GAME:modes();
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

void modes()
{
	cout << "[1] NORMAL" << endl;
	cout << "[2] WORM INVASION" << endl;
	cout << "[3] SWIRL" << endl;
	cout << "[4] MAIN MENU" <<endl;

	int input;
	for(int check = 0; check == 0;)
	{
		input = getch() - 48;
		state stage = ONE;
		while(stage != END)
		{
			if(input == 1)
			{
				system("cls");
ONE:play();
				system("pause");
			}

			else if (input == 2)
			{
				system("cls");
TWO:play();
				system("pause");
			}

			else if (input == 3)
			{
				system("cls");
THREE:play();
				system("pause");
			}

			else if (input == 4)
			{
				system("cls");
FOUR:startscreen();
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

void gameover()
{
	system("cls");
	colour(0x07);

	cout<<  "  ******    ***    *****        ***** **********        *****      ***          ***   ********** ***********           \n"
		" ********  *****   **  **      **  ** **********      ***   ***    ***          ***   ********** *************         \n"
		" ***  *** **   **  **   **    **   ** *****          ***     ***   ***          ***   *****      ****        ****      \n"
		" ***      **   **  **    **  **    ** *****         ****     ****  ***          ***   *****      ****         ****     \n"
		" ***      *******  **     ***      ** **********    ****     ****  ***          ***   ********** ****        ****      \n"
		" ***  *** *******  **              ** *****          ***     ***    ***        ***    *****      *************         \n"
		" ******** **   **  **              ** *****           ***   ***       ***     ***     *****      ****       ***        \n"
		"  ******  **   **  **              ** **********        *****           ******        ********** ****         ****       " << endl;

	cout << endl;

	cout << "THANKS FOR PLAYING, YOUR FINAL SCORE: " << score;

	exit(1);
}

void endscreen()
{
	system("cls");
	colour(0x07);

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
		" ****   **** ***       ***             ****      ***     ***  ****  ****	\n"
		"  *********  ********* *********       ****       ***   ***    ********	\n"
		"   ******    ********* *********       ****         *****       ******   " << endl;

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
	colour(0x07);

	cout << endl;
	cout << "Newbie... you think you have what it takes to be a CATCH NINJA huh?" << endl << endl << endl;

	cout << "HOW TO PLAY: " << endl << endl;

	cout << "1) Catch the fruits with the basket!" << endl;
	cout << "2) Avoid the nasty worms!" << endl;
	cout << "3) Be the best Catch Ninja you can be!" << endl << endl << endl;

	cout << "FRUITS CATCHER ROOKIE GUIDE 101:" << endl << endl;

	cout << "1) APPLE - 1 POINT ";
	colour(0x0C);
	cout << "      [ O ]" << endl;

	colour(0x07);
	cout << "2) ORANGE - 3 POINT ";
	colour(0x04);
	cout << "     [ O ]" << endl;

	colour(0x07);
	cout << "3) GRAPE - 2X LE POINTS ";
	colour(0x05);
	cout << " [ O ]" << endl << endl << endl;

	colour(0x07);
	cout << "NASTY THINGS TO BEWARE OF: " << endl << endl;

	colour(0x07);
	cout << "1) WORM - 5 POINT DEDUCTION";
	colour(0x08);
	cout << " [ ~ ]" << endl << endl << endl;

	colour(0x07);
	cout << "CREATORS: " << endl << endl;
	cout << "Giggs" << endl;
	cout << "Rayson" << endl;
	cout << "Ruoyun" << endl;
	cout << "Jessica" << endl << endl;

	colour(0x07);
	cout << "DIFFICULTY: " << endl << endl;
	cout << "[1] EASY"  << endl;
	cout << "[2] NORMAL"<< endl;
	cout << "[3] HARD"  << endl;
	cout << "[4] MAIN MENU" <<endl << endl;

	int input;
	for(int check = 0; check == 0;)
	{
		input = getch() - 48;
		diff stage = EASY;
		while(stage != END)
		{
			if(input == 1)
			{
				system("cls");
EASY:;
				system("pause");
			}

			else if (input == 2)
			{
				system("cls");
NORMAL:;
				system("pause");
			}

			else if (input == 3)
			{
				system("cls");
HARD:;
				system("pause");
			}

			else if(input == 4)
			{
				system("cls");
MAINMENU:startscreen();
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

	exit(1);
}

void scoreboard()
{
	system("cls");
	colour(0x07);

	cout << "****        **********  ********         ********        **********  ********       " <<
		endl << "****        **********  *********        ****  ****      **********  ****  ****      " <<
		endl << "****        ****        ****  ****       ****    ****    ****        ****   ****      " <<
		endl << "****        ********    ***********      ****     ****   ********    ****  *****       " <<
		endl << "****        ********    ************     ****     *****  ********    *********          " <<
		endl << "****        ****        ****     ****    ****    *****   ****        **** ****           " <<
		endl << "**********  **********  ****      ****   ****  ******    **********  ****  ****           " <<
		endl << "**********  **********  ****       ****  **********      **********  ****   *****          " <<

		endl << endl <<

		endl << "*********      **********    ********         ********      *******         " <<
		endl << "****   ****   *****   ****   *********        ****  ****    ****  ****       " <<
		endl << "****   ****   ****     ****  ****  ****       ****   ****   ****    ****      " <<
		endl << "*********     ****     ****  ***********      ****  *****   ****     ****      " <<
		endl << "**** ****     ****     ****  ************     *********     ****    *****       " <<
		endl << "****   *****  ****     ****  ****     ****    **** ****     ****    *****        " <<
		endl << "****   *****   ****  *****   ****      ****   ****  ****    ****  ******          " <<
		endl << "***********     *********    ****       ****  ****   *****  **********             " <<
		endl <<
		endl << endl;

	int first, second, third, forth, fifth;

	cout << "TOP 5 NINJA HIGH SCORES: " << endl << endl;

	ifstream indata1;
	ofstream outdata1;
	string data1;
	indata1.open("score1.txt");
	outdata1.open("temp1.txt");

	while (!indata1.eof())
	{
		getline(indata1, data1);
		first = stoi(data1);
	}

	ifstream indata2;
	ofstream outdata2;
	string data2;
	indata2.open("score2.txt");
	outdata2.open("temp2.txt");

	while (!indata2.eof())
	{
		getline (indata2, data2);
		second = stoi(data2);
	}

	ifstream indata3;
	ofstream outdata3;
	string data3;
	indata3.open("score3.txt");
	outdata3.open("temp3.txt");

	while (!indata3.eof())
	{
		getline (indata3, data3);
		third = stoi(data3);
	}

	ifstream indata4;
	ofstream outdata4;
	string data4;
	indata4.open("score4.txt");
	outdata4.open("temp4.txt");

	while (!indata4.eof())
	{
		getline (indata4, data4);
		forth = stoi(data4);
	}

	ifstream indata5;
	ofstream outdata5;
	string data5;
	indata5.open("score5.txt");
	outdata5.open("temp5.txt");

	while (!indata5.eof())
	{
		getline (indata5, data5);
		fifth = stoi(data5);
	}	

	int highscore[5] = {first, second, third, forth, fifth};
	int subsitute = 0;
	int subsitute2 = 0;
	int size = sizeof(highscore)/sizeof(highscore[0]);
	cout << size;

	for(int a = 0; a < size; a++)
	{
		if(score > highscore[a])
		{
			subsitute = highscore[a];
			highscore[a] = score;
			score = 0;
		}

		else if(subsitute > highscore[a])
		{
			subsitute2 = highscore[a];
			highscore[a] = subsitute;
			subsitute = 0;
		}

		else if(subsitute2 > highscore[a])
		{
			subsitute = highscore[a];
			highscore[a] = subsitute2;
			subsitute2 = 0;
		}
		cout << highscore[a] << endl;
	}

	outdata1 << highscore[0];
	outdata2 << highscore[1];
	outdata3 << highscore[2];
	outdata4 << highscore[3];
	outdata5 << highscore[4];

	indata1.close ();
	indata2.close ();
	indata3.close ();
	indata4.close ();
	indata5.close ();

	outdata1.close ();
	outdata2.close ();
	outdata3.close ();
	outdata4.close ();
	outdata5.close ();

	remove("score1.txt");
	rename("temp1.txt", "score1.txt");

	remove("score2.txt");
	rename("temp2.txt", "score2.txt");

	remove("score3.txt");
	rename("temp3.txt", "score3.txt");

	remove("score4.txt");
	rename("temp4.txt", "score4.txt");

	remove("score5.txt");
	rename("temp5.txt", "score5.txt");

	cout << endl;
	cout << "[1] MAIN MENU" <<endl;
	cout << "[2] EXIT" << endl;

	int input;

	for(int check = 0; check == 0;)
	{
		input = getch() - 48;
		state stage = GAME;

		while(stage != END)
		{
			if (input == 1)
			{
				system("cls");
MAINMENU:startscreen();
				system("pause");
			}

			else if(input == 2)
			{
				endscreen();
			}

			else
			{
				cout << "Invalid input!" << endl;
				input = getch() - 48;
				check++;
			}
		}
	}

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