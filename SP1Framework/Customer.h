#pragma once
#include "Entity.h"
class Customer :
    public Entity
{
private:
    int itemToBuy;//to determine which item the customer is going to buy
    int quantity;//to determine how many of the item the customer is going to buy

public:
    Customer();
    ~Customer();
    void moveToShelfContainingItem(int itemToBuy);
    bool entranceWaiting(void);
    bool shelfWaiting(void);
};

