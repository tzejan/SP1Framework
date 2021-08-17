#pragma once
#include "entity.h"
#include <iostream>
class Player :
    public entity
{
private:

public:

    Player();
    void movement(int dir);
    
};

