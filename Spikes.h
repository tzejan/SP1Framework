#pragma once
#include "Entity.h"
class Spikes : public Entity
{
private:
	bool SpikeActive;
public:
	Spikes(int, int,bool);
	~Spikes();
	char GetSymbol(void);
	void SpikesActivity(void);
};

