#include "Player.h"
#include <iostream>
#include <conio.h>  //Get Keyboard Input
#include <Windows.h>

int Player::direction = 0;
int Player::Moves = 0;
Player::Player(int x,int y)
{
    this->SetEntityPosition(x, y);
    HaveKey = false;
}

Player::~Player()
{
}

void Player::move(void)
{
    system("pause>nul");
    if (isVirtualKeyPressed(VK_UP))
    {
        this->DoMovement(-1, 0);
        SetPlayerDirection(1);
    }
    else if (isVirtualKeyPressed(VK_DOWN))
    {
        this->DoMovement(1, 0);
        SetPlayerDirection(2);
    }
    else if (isVirtualKeyPressed(VK_LEFT))
    {
        this->DoMovement(0, -1);
        SetPlayerDirection(3);
    }
    else if (isVirtualKeyPressed(VK_RIGHT))
    {
        this->DoMovement(0, 1);
        SetPlayerDirection(4);
    }
}

void Player::DoMovement(int x,int y)
{
    this->SetEntityPosition((this->GetEntityPosition()).getx()+x, (this->GetEntityPosition()).gety()+y);
    Player::MovesDecreaseByOne();
}

char Player::GetSymbol(void)
{
	return 'P';
}

void Player::SetHaveKey(bool Key)
{
    this->HaveKey = Key;
}

bool Player::GetHaveKey(void)
{
    return HaveKey;
}

void Player::SetPlayerDirection(int Direct)
{
    direction = Direct;
}

int Player::GetPlayerDirection(void)
{
    return direction;
}

void Player::MovesDecreaseByOne(void)
{
    Moves--;
}
void Player::SetMoves(int NewMoves)
{
    Moves = NewMoves;
}
int Player::GetMoves(void)
{
    return Moves;
}