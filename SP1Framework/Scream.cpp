#include "Scream.h"

Scream::Scream(Graphics& console)
	:
console(console),
power(0),
opposingForce(0),
currFrame(0),
pauseDelay(0),
paused(true),
gameends(false)
{
}

Scream::~Scream()
{
}

void Scream::draw()
{
}

gamestate Scream::update()
{
	if(isKeyPressed(VK_RETURN) && pauseDelay == 0)
	{
		paused = !paused;
		pauseDelay = 5;
	}
	if(pauseDelay != 0)
	{
		pauseDelay--;
	}
	//will only update the current frame once unpaused
	if(paused)
	{
		console.draw(10,10,"Paused",0x1A);
		return SCREAM;
	}
	else
	{
		currFrame++;
		gameends = play();
		draw();
		if(gameends)
		{
			gamestate state = (gamestate)(rand() % numofminigames + 1);
			return state;
		}
		return SCREAM;
	}
}

bool Scream::play()
{
	return false;
}