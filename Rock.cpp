#include "Rock.h"
#include "Player.h"

Rock::Rock(int x, int y)
{
    this->SetEntityPosition(x, y);
}

Rock::~Rock()
{
}

void Rock::move(void)
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

void Rock::DoMovement(int x, int y)
{
    this->SetEntityPosition((this->GetEntityPosition()).getx() + x, (this->GetEntityPosition()).gety() + y);
}

char Rock::GetSymbol(void)
{
    return 'R';
}
