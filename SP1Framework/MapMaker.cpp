#include "MapMaker.h"

MapMaker::MapMaker() : no_of_row(0), no_of_col(0)
{
	MapArray = NULL;
}

MapMaker::~MapMaker()
{
	for (int i = 0; i < no_of_row; i++) {
		delete[] MapArray[i];
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
		//Gets size of map
		while (getline(file_, Map))
		{
			no_of_col = static_cast<int>(Map.length());
			cout << Map[row] << endl;
			no_of_row++;

		}
		//Allocate Memory for MapArray
		MapArray = new char* [no_of_row];
		for (int i = 0; i < no_of_row; i++) {
			MapArray[i] = new char[no_of_col];
		}


		//Resets the getline
		file_.clear();
		file_.seekg(0, ios::beg);

		//Puts each character in the file in the array
		while (getline(file_, Map))
		{
			for (int i = 0; i < Map.length(); i++) {
				MapArray[row][i] = Map[i];
			}
			row++;
		}
		file_.close();
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

char** MapMaker::getMapArray()
{
	return MapArray;
}

int MapMaker::getEntityCount()
{
	int count = 0;
	for (int row = 0; row < (sizeof(getMapArray()) / sizeof(*getMapArray())); row++) {
		for (int col = 0; col < (sizeof(getMapArray()[row]) / sizeof(*getMapArray()[row])); col++) {
			switch (getFromCoord(col, row)) {
			case 'P':
			case 'G':
			case ']':
			case '[':
			case '&':
			case '%':
			case '$':

				count++;
				break;
			default:
			}
		}
	}
	return count;
}





