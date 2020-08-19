#include "Map.h"

void Map::drawMap()
{
    for (int i = 0; i < 79; i++)
    {
        if (i < 17 || i > 28 && i < 51 || i > 63 && i < 79)
        {
            MapArray[i][4] = '*';
            MapArray[i][10] = '*';
            MapArray[i][14] = '*';
            MapArray[i][20] = '*';
        }
    }
    for (int i = 0; i < 25; i++)
    {
        if (i < 5 || i > 9 && i < 15 || i > 19 && i < 25)
        {
            MapArray[15][i] = '*';
            MapArray[29][i] = '*';
            MapArray[50][i] = '*';
            MapArray[64][i] = '*';
        }
    }
    // Gray colour oF ROAD
    for (int i = 17; i < 28; i++)
    {
        for (int r = 0; r < 25; r++)
        {
            MapArray[i][r] = '@';
        }
    }
}


char Map::GetMapArray()
{
  for (int i = 0; i < 79; i++)
  {
      for (int c = 0; c < 25; c++)
      {
          return MapArray[i][c];
      }
  }
}
 
