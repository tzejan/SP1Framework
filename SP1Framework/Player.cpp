#include "Player.h"

player::player(SGameChar* playerptr)
{
	this->playerptr = playerptr;
	direction = 'U';
}

player::~player()
{
}

char player::GetDirection()
{
	return direction;
}

void player::SetDirection(char dirc)
{
	direction = dirc;
}
