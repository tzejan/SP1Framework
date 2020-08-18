#pragma once
#include "Entity.h"
class Son :
    public Entity
{
private:
    bool bSick;

public:
    Son();
    ~Son();

    void isSick(); //Son falls sick, bSick = true
    void Recovers(); //son recovers, bSick = false
    bool getStatus(); //return bSick

    void ChancesOfFallingSick(Son s); 
};

