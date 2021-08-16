#include "entity.h"

int entity::getCoordX()
{
    return Location.X;
}

int entity::getCoordY()
{
    return Location.Y;
}

void entity::setCoordX(int i)
{
    Location.X = i;
}

void entity::setCoordY(int i)
{
    Location.Y = i;
}

void entity::setm_bActive(bool i)
{
    m_bActive = i;
}
