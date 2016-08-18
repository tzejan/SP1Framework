#include "PushBox_Level.h"

void doorMapChanges_J()
{
	//Doors:
	if (map[6][106] == (char)254) //Door1 
	{
		map[5][82] = ' ';
		map[5][83] = ' ';
	}

	if (map[11][119] == (char)254) //Door2
	{
		map[24][96] = ' ';
		map[24][97] = ' ';
	}

	if (map[21][85] == (char)254) //Door3
	{
		map[21][86] = ' ';
		map[4][57] = ' ';
		map[4][58] = ' ';
	}

	if (map[9][69] == (char)254) //Door4
	{
		map[9][70] = ' ';
		map[14][80] = ' ';
		map[14][81] = ' ';
	}

	if (map[14][22] == (char)254) //Door5
	{
		map[1][30] = ' ';
		map[1][31] = ' ';
	}

	if (map[1][12] == (char)254) //Door6
	{
		map[5][12] = ' ';
		map[5][13] = ' ';
	}

	if (map[11][18] == (char)254) //Door7
	{
		map[11][19] = ' ';
		map[21][7] = ' ';
		map[21][8] = ' ';
	}

	if (map[31][15] == (char)254) //Door8
	{
		map[31][16] = ' ';
		map[34][29] = ' ';
		map[34][30] = ' ';
	}
}