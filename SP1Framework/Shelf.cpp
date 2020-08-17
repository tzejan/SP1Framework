#include "Shelf.h"

Shelf::Shelf() : capacity{ 20 } , amount{0} , itemtag{ ' ' }
{
}

Shelf::~Shelf()
{
}

int Shelf::getCapacity()
{
    return capacity;
}

int Shelf::getAmount()
{
    return amount;
}

void Shelf::setAmount(int amount)
{
    this->amount = amount;
}

int Shelf::getItemtag()
{
    return itemtag;
}

void Shelf::setItemtag(int itemtag)
{
    this->itemtag = itemtag;
}
