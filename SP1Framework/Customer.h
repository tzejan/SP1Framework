#pragma once
#include "Entity.h"
class Customer :
    public Entity
{
private:
    int itemToBuy;
    int quantity;

public:
    Customer();
    ~Customer();
    void moveToShelfContainingItem(int itemToBuy);
    bool entranceWaiting(void);
    bool shelfWaiting(void);
};

