#pragma once
#include "entity.h"
#include <iostream>
class Player :
    public entity
{
private:
    int hp;
public:

    Player();
    void movement(int dir);

    //player is the only one with hp
    void setHp(int h);
    int getHp();
    
};

