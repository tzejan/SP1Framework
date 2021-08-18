#pragma once
#include "entity.h"
#include <iostream>

class bullet :
    public entity
{
private:
    int direection;
public:
    bullet();
    bullet(int posX,int  posY,int dir);

    void movement(int dir);

    int GetDirection();
};

