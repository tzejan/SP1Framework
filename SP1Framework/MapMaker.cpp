#include "MapMaker.h"

MapMaker::MapMaker():MapArray { ' ' }
{
}

MapMaker::~MapMaker()
{
}

void MapMaker::Draw(string filepath)
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
