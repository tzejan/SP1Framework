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

void entity::setSym(char a)
{
    sym = a;
}

char entity::getSym()
{
    return sym;
}

float entity::getSpeed()
{
    return speed;
}

void entity::setspeed(float i)
{
    speed = i;
}
