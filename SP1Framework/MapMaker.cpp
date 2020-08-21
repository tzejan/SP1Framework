#include "MapMaker.h"

MapMaker::MapMaker():MapArray { ' ' }
{
}

MapMaker::~MapMaker()
{
}

void MapMaker::Load(string filepath)
{
	string Map;
	int row = 0;
	ifstream file_(filepath);
	if (file_.is_open()) {
		while (getline(file_, Map))
		{
			for (int i = 0; i < static_cast<int>(Map.length()); i++) {
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





