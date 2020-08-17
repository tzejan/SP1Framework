#pragma once
#include "Entity.h"
class Customer :
    public Entity
{
private:
    int itemToBuy;

public:
    Customer();
    ~Customer();
    
};

