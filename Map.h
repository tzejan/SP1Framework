#pragma once
#include <iostream>
#include "Sprite.h"

class Map
{
private:
    char GameMap[20][20];
public:
    Map();
    ~Map();
    void PrintGameMap(void);  //Outputs the game map UI
    void SetGameMap(int x, int y, char symbol);  //Set the entities onto the game map
    static std::string GetMapChosen(int);
    static int GetMapMoves(int);
    std::string ASCIItoString(std::string);
};
