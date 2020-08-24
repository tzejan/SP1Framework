#include "MapMaker.h"

MapMaker::MapMaker()
{
	MapArray = NULL;
	no_of_rows = 0;
	no_of_col = 0;
}

MapMaker::~MapMaker()
{
	for (int row = 0; row < no_of_rows; row++) {
		delete[] MapArray[row];
	}
	delete[] MapArray;
	MapArray = NULL;
}

void MapMaker::Load(string filepath)
{
	string Map;
	int row = 0;
	ifstream file_(filepath);
	if (file_.is_open()) {

		//Gets no_of_col and no_of_row based on file
		while (getline(file_, Map))
		{
			no_of_col = static_cast<int>(Map.length());
			
			no_of_rows++;
		}


		



		
		file_.close();
	}
	MapArray = new char* [no_of_rows];
	for (int row = 0; row < no_of_rows; row++) {
		MapArray[row] = new char[no_of_col];
	}
	ifstream file2_(filepath);
	if (file2_.is_open()) {

		while (getline(file2_, Map))
		{
			for (int col = 0; col < no_of_col; col++) {
				MapArray[row][col] = Map[col];
			}
			row++;

		}

		file2_.close();
	}
}

void MapMaker::Render(COORD origin, COORD end, Console& g_Console)
{
	COORD c;

	for (int x = origin.X; x < end.X; x++) {
		c.X = x;
		for (int y = origin.Y; y < end.Y; y++) {
			c.Y = y;
			g_Console.writeToBuffer(c, MapArray[y - origin.Y][x - origin.X]);
		}
	}
}

void MapMaker::Render(SHORT origin_x, SHORT origin_y, SHORT end_x, SHORT end_y, Console& g_Console)
{
	COORD origin, end;
	origin.X = origin_x;
	origin.Y = origin_y;
	end.X = end_x;
	end.Y = end_y;

	Render(origin, end, g_Console);
}

char MapMaker::getFromCoord(COORD c)
{
	return MapArray[c.Y][c.X];
}

char MapMaker::getFromCoord(SHORT x, SHORT y)
{

	return MapArray[y][x];

}



