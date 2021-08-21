#include "Skeleton.h"
#include "Player.h"

Skeleton::Skeleton(int x, int y)
{
	this->SetEntityPosition(x, y);
}

Skeleton::~Skeleton()
{

}
char Skeleton::GetSymbol(void)
{
	return 'S';
}

void Skeleton::move(void)
{
    if (Player::GetPlayerDirection() == 1)
    {
        this->DoMovement(-1, 0);
    }
    else if (Player::GetPlayerDirection() == 2)
    {
        this->DoMovement(1, 0);
    }
    else if (Player::GetPlayerDirection() == 3)
    {
        this->DoMovement(0, -1);
    }
    else if (Player::GetPlayerDirection() == 4)
    {
        this->DoMovement(0, 1);
    }
}

void Skeleton::DoMovement(int x , int y)
{
    this->SetEntityPosition((this->GetEntityPosition()).getx() + x, (this->GetEntityPosition()).gety() + y);
}
