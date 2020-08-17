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

signed char Shelf::getItemtag()
{
    return itemtag;
}

void Shelf::setItemtag(signed char itemtag)
{
    this->itemtag = itemtag;
}
