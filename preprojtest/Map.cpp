#include "Map.h"

Map::Map()
{
    is_stolen = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::string temp_string = "";
            temp_string += i;
            temp_string += j;
            get_map_grid(i, j).set_room_pos(temp_string);
        }
    }
}

Map::~Map()
{
}

char Map::get_minmap_char(int x, int y)
{
    return minmap[y][x];
}

Grid Map::get_map_grid(int x, int y)
{
    return level_map[y][x];
}

void Map::update_minmap_char(std::string room_number)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            minmap[j][i] = ' ';
        }
    }
    int i = room_number[0] - '0';
    int j = room_number[1] - '0';
    minmap[i][j] = 'X';
}
