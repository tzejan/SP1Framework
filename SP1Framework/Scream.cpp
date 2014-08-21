#include "Scream.h"

Scream::Scream(Graphics& console)
	:
console(console),
power(0),
resistance(0),
currFrame(0),
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
	if(isKeyPressed(VK_RETURN))
	{
		paused = !paused;
	}
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
			gamestate state = (gamestate)(rand() % numofminigames);
			return state;
		}
		return SCREAM;
	}
}

bool Scream::play()
{
	return false;
}