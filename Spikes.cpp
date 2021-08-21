#include "Spikes.h"
Spikes::Spikes(int x, int y,bool z)
{
	this->SetEntityPosition(x, y);
	SpikeActive = z;

}
Spikes::~Spikes()
{

}

char Spikes::GetSymbol(void)
{
	if (this->SpikeActive == true)
	{
		return 'I';
	}
	else
	{
		return 'i';
	};
}


void Spikes::SpikesActivity(void)
{
	if (this->SpikeActive == true)
	{
		this->SpikeActive = false;
	}
	else
	{
		this->SpikeActive = true;
	}
}