#include "PushBox_Level.h"
int door = 0;
void doorMapChanges_J()
{
	//Doors:
	if (map[6][106] == (char)254 && door == 0) //Door1 
	{
		map[6][107] = ' ';
		map[5][82] = ' ';
		map[5][83] = ' ';
		door = 1;
	}

	if (map[11][119] == (char)254 && door == 1) //Door2
	{
		map[11][120] = ' ';
		map[24][96] = ' ';
		map[24][97] = ' ';
		door = 2;
	}

	if (map[21][85] == (char)254 && door == 2) //Door3
	{
		map[21][86] = ' ';
		map[4][57] = ' ';
		map[4][58] = ' ';
		door = 3;
	}

	if (map[9][69] == (char)254 && door == 3) //Door4
	{
		map[9][70] = ' ';
		map[14][80] = ' ';
		map[14][81] = ' ';
		door = 4;
	}

	if (map[14][22] == (char)254 && door == 4) //Door5
	{
		map[1][30] = ' ';
		map[1][31] = ' ';
		door = 5;
	}

	if (map[1][12] == (char)254 && door == 5) //Door6
	{
		map[5][12] = ' ';
		map[5][13] = ' ';
		door = 6;
	}

	if (map[11][18] == (char)254 && door == 6) //Door7
	{
		map[11][19] = ' ';
		map[21][7] = ' ';
		map[21][8] = ' ';
		door = 7;
	}

	if (map[31][15] == (char)254 && door == 7) //Door8
	{
		map[31][16] = ' ';
		map[34][29] = ' ';
		map[34][30] = ' ';
		door = 8;
	}
}